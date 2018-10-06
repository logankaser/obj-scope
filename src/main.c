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

void print_matrix(t_mat *m)
{
	printf("%+.3f, %+.3f, %+.3f, %+.3f\n", m->m[0][0], m->m[0][1], m->m[0][2], m->m[0][3]);
	printf("%+.3f, %+.3f, %+.3f, %+.3f\n", m->m[1][0], m->m[1][1], m->m[1][2], m->m[1][3]);
	printf("%+.3f, %+.3f, %+.3f, %+.3f\n", m->m[2][0], m->m[2][1], m->m[2][2], m->m[2][3]);
	printf("%+.3f, %+.3f, %+.3f, %+.3f\n\n", m->m[3][0], m->m[3][1], m->m[3][2], m->m[3][3]);
}

void translation_matrix(double x, double y, double z, t_mat *mat)
{
	mat->order = 4;
	MAT_ROW(mat->m[0], 1, 0, 0, 0);
	MAT_ROW(mat->m[1], 0, 1, 0, 0);
	MAT_ROW(mat->m[2], 0, 0, 1, 0);
	MAT_ROW(mat->m[3], x, y, z, 1);
}

void	render(t_scop *scop)
{
	static int i = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	translation_matrix(0.0, 0.0, -4, &scop->trans);
	glUniformMatrix4fv(scop->trans_id, 1, GL_FALSE, (GLfloat*)scop->trans.m);
	mat_x_mat_res(&scop->proj, &scop->trans, &scop->tp);
	if (i++ % 60 == 0)
	{
		//print_matrix(&scop->tp);
	}
	glUniformMatrix4fv(scop->tp_id, 1, GL_FALSE, (GLfloat*)scop->tp.m);
	glDrawArrays(GL_TRIANGLES, 0, scop->vert_count);
}

void	validate_shader(GLuint shader)
{
	GLint	success;
	GLint	log_size;
	char	*log;

	success = 0;
	log_size = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
		log = malloc(log_size);
		glGetShaderInfoLog(shader, log_size, NULL, log);
		printf("%s\n", log);
		free(log);
		exit(1);
	}
}

GLuint	compile_shader(const char *path, GLenum shader_type)
{
	size_t	size;
	FILE	*shader_file;
	char	*shader_str;
	GLuint	id;

	if ((shader_file = fopen(path, "r")) == NULL)
	{
		perror("File error");
		exit(1);
	}
	fseek(shader_file, 0L, SEEK_END);
	size = ftell(shader_file);
	rewind(shader_file);
	shader_str = malloc(size);
	fread(shader_str, 1, size + 1, shader_file);
	shader_str[size] = '\0';
	fclose(shader_file);
	id = glCreateShader(shader_type);
	glShaderSource(id, 1, (const GLchar**)&shader_str, NULL);
	glCompileShader(id);
	free(shader_str);
	validate_shader(id);
	return (id);
}

void	validate_program(GLuint program_id)
{
	GLint	success;
	GLint	log_size;
	char	*log;

	glGetProgramiv(program_id, GL_LINK_STATUS, &success);
	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_size);
	if (success == GL_FALSE)
	{
		glGetShaderiv(program_id, GL_INFO_LOG_LENGTH, &log_size);
		log = malloc(log_size);
		glGetProgramInfoLog(program_id, log_size, NULL, log);
		printf("%s\n", log);
		exit(1);
	}
}

GLuint	make_program(const char *frag, const char *vert)
{
	GLuint frag_id;
	GLuint vert_id;
	GLuint program_id;

	frag_id = compile_shader(frag, GL_FRAGMENT_SHADER);
	vert_id = compile_shader(vert, GL_VERTEX_SHADER);
	program_id = glCreateProgram();
	glAttachShader(program_id, vert_id);
	glAttachShader(program_id, frag_id);
	glLinkProgram(program_id);
	validate_program(program_id);
	glDetachShader(program_id, vert_id);
	glDetachShader(program_id, frag_id);	
	glDeleteShader(vert_id);
	glDeleteShader(frag_id);
	return (program_id);
}

static void open_obj(t_scop *scop)
{
	t_uvector	vert;
	t_uvector	uv;
	t_uvector	norm;
	FILE		*obj_file;
	GLuint		buffer_id[3];

	if ((obj_file = fopen("assets/monkey_fancy.obj", "r")) == NULL)
		perror("File error");
	ft_uvector_init(&vert, sizeof(t_vec3));
	ft_uvector_init(&uv, sizeof(t_vec2));
	ft_uvector_init(&norm, sizeof(t_vec3));
	load_obj(obj_file, &vert, &uv, &norm);
	fclose(obj_file);
	scop->vert_count = vert.length;
	//t_vec3	tmp;
	//t_vec2	tmp_uv;
	//for (unsigned i = 0; i < norm.length; ++i)
	//{
	//	tmp = *(t_vec3*)ft_uvector_get(&norm, i, 0);
	//	printf("v(%+.3f,%+.3f,%+.3f)\n", tmp.x, tmp.y, tmp.z);
	//}
	//while (ft_uvector_pop(&uv, &tmp_uv))
	//	printf("u(%+.3f,%+.3f) ", tmp_uv.x, tmp_uv.y);
	//while (ft_uvector_pop(&norm, &tmp))
	//	printf("n(%+.3f,%+.3f,%+.3f) ", tmp.x, tmp.y, tmp.z);
	//printf("\n");

	glGenBuffers(3, buffer_id);

	glBindBuffer(GL_ARRAY_BUFFER, buffer_id[0]);
	glBufferData(GL_ARRAY_BUFFER, vert.length * 3 * sizeof(float),
	vert.data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, buffer_id[1]);
	glBufferData(GL_ARRAY_BUFFER, uv.length * 2 * sizeof(float),
	uv.data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);


	glBindBuffer(GL_ARRAY_BUFFER, buffer_id[2]);
	glBufferData(GL_ARRAY_BUFFER, norm.length * 3 * sizeof(float),
	norm.data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

int		main(void)
{
	EmscriptenWebGLContextAttributes attrs;
	emscripten_webgl_init_context_attributes(&attrs);
	attrs.depth = 1;
	attrs.stencil = 1;
	attrs.antialias = 1;
	attrs.majorVersion = 2;
	attrs.minorVersion = 0;

	EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context = emscripten_webgl_create_context("canvas", &attrs);
	emscripten_webgl_make_context_current(context);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor(0.4,  0.1,  0.1,  1);
	GLuint prog = make_program("assets/frag.glsl", "assets/vert.glsl");
	glUseProgram(prog);

	t_scop *scop = malloc(sizeof(t_scop));
	scop->tp_id = glGetUniformLocation(prog, "TP");
	scop->trans_id = glGetUniformLocation(prog, "T");
	scop->proj.order = 4;
	scop->trans.order = 4;
	scop->tp.order = 4;

	// VAO
	glGenVertexArrays(1, &scop->vao_id);
	// Enable VAO
	glBindVertexArray(scop->vao_id);
	open_obj(scop);
	MAT_ROW(scop->proj.m[0], 2.39012, 0, 0, 0);
	MAT_ROW(scop->proj.m[1], 0, 1.79259, 0, 0);
	MAT_ROW(scop->proj.m[2], 0, 0, -1.002, -1);
	MAT_ROW(scop->proj.m[3], 0, 0, -0.2002, 0);

	MAT_ROW(scop->trans.m[0], 1, 0, 0, 0);
	MAT_ROW(scop->trans.m[1], 0, 1, 0, 0);
	MAT_ROW(scop->trans.m[2], 0, 0, 1, 0);
	MAT_ROW(scop->trans.m[3], 0, 0, 0, 1);
	memcpy(&scop->tp.m, &scop->proj.m, sizeof(float) * 16);
	emscripten_set_main_loop_arg((em_arg_callback_func)render, scop, -1, 0);
	return (0);
}
