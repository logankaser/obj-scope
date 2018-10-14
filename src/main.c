/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 11:58:07 by lkaser            #+#    #+#             */
/*   Updated: 2018/08/02 12:00:07 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#include "uvector.h"
#include "matrix.h"
#include "obj.h"
#include "scop.h"

static unsigned g_vertex_count = 0;

static void	main_loop(t_scop *scop)
{
	handle_input(scop);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	MAT_ROW(scop->trans.m[0], 1, 0, 0, 0);
	MAT_ROW(scop->trans.m[1], 0, 1, 0, 0);
	MAT_ROW(scop->trans.m[2], 0, 0, 1, 0);
	MAT_ROW(scop->trans.m[3], 0, 0, 0, 1);
	mat_rotate_x(scop->rot.x, &scop->trans);
	mat_rotate_y(scop->rot.y, &scop->trans);
	mat_rotate_z(scop->rot.z, &scop->trans);
	mat_translate(scop->pos.x, scop->pos.y, scop->pos.z - 4.0, &scop->trans);
	glUniformMatrix4fv(scop->trans_id, 1, GL_FALSE, (GLfloat*)scop->trans.m);
	mat_x_mat_res(&scop->proj, &scop->trans, &scop->tp);
	glUniformMatrix4fv(scop->tp_id, 1, GL_FALSE, (GLfloat*)scop->tp.m);
	glDrawArrays(GL_TRIANGLES, 0, g_vertex_count);
}

static void	default_texture(t_scop *scop)
{
	static uint8_t data[16] = {
		0, 255, 100, 255,
		0, 255, 100, 255,
		0, 255, 100, 255,
		0, 255, 100, 255
	};

	glGenTextures(1, &scop->tex_id);
	glBindTexture(GL_TEXTURE_2D, scop->tex_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
}

#define GL_VEC3 (3 * sizeof(GLfloat))
#define GL_VEC2 (3 * sizeof(GLfloat))

void		obj_open(FILE *obj_file)
{
	t_uvector	vt;
	t_uvector	uv;
	t_uvector	nl;
	GLuint		buffer_id[3];

	obj_load(obj_file, &vt, &uv, &nl);
	obj_normalize(&vt);
	g_vertex_count = vt.length;
	glGenBuffers(3, buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id[0]);
	glBufferData(GL_ARRAY_BUFFER, vt.length * GL_VEC3, vt.data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id[1]);
	glBufferData(GL_ARRAY_BUFFER, uv.length * GL_VEC2, uv.data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id[2]);
	glBufferData(GL_ARRAY_BUFFER, nl.length * GL_VEC3, nl.data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	free(vt.data);
	free(uv.data);
	free(nl.data);
}

static void	init_opengl(t_scop *scop)
{
	EmscriptenWebGLContextAttributes	attrs;
	EMSCRIPTEN_WEBGL_CONTEXT_HANDLE		context;
	GLuint								prog;

	emscripten_webgl_init_context_attributes(&attrs);
	attrs.majorVersion = 2;
	context = emscripten_webgl_create_context("canvas", &attrs);
	emscripten_webgl_make_context_current(context);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor(0.1, 0.1, 0.12, 1);
	prog = make_program("assets/scop.frag", "assets/scop.vert");
	glUseProgram(prog);
	scop->tp_id = glGetUniformLocation(prog, "TP");
	scop->trans_id = glGetUniformLocation(prog, "T");
	scop->proj.order = 4;
	scop->trans.order = 4;
	scop->tp.order = 4;
	default_texture(scop);
}

int			main(void)
{
	FILE								*obj_file;
	t_scop								*scop;

	scop = calloc(1, sizeof(t_scop));
	init_opengl(scop);
	glGenVertexArrays(1, &scop->vao_id);
	glBindVertexArray(scop->vao_id);
	if ((obj_file = fopen("assets/42.obj", "r")) == NULL)
		perror("File error");
	obj_open(obj_file);
	fclose(obj_file);
	MAT_ROW(scop->proj.m[0], 2.39012, 0, 0, 0);
	MAT_ROW(scop->proj.m[1], 0, 1.79259, 0, 0);
	MAT_ROW(scop->proj.m[2], 0, 0, -1.002, -1);
	MAT_ROW(scop->proj.m[3], 0, 0, -0.2002, 0);
	MAT_ROW(scop->trans.m[0], 1, 0, 0, 0);
	MAT_ROW(scop->trans.m[1], 0, 1, 0, 0);
	MAT_ROW(scop->trans.m[2], 0, 0, 1, 0);
	MAT_ROW(scop->trans.m[3], 0, 0, 0, 1);
	emscripten_set_main_loop_arg((em_arg_callback_func)main_loop, scop, -1, 0);
	emscripten_set_keydown_callback("body", scop, 0, key_down);
	emscripten_set_keyup_callback("body", scop, 0, key_up);
	return (0);
}
