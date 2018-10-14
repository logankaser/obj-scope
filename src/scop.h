/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 19:39:33 by lkaser            #+#    #+#             */
/*   Updated: 2018/10/13 19:41:05 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H
# include <GLES3/gl3.h>
# include "matrix.h"

typedef struct	s_scop
{
	GLuint		tp_id;
	GLuint		trans_id;
	GLuint		tex_id;
	GLuint		vao_id;
	unsigned	vert_count;
	t_mat		proj;
	t_mat		trans;
	t_mat		tp;
	char		key[255];
	t_vec3		rot;
	t_vec3		pos;
}				t_scop;

EM_BOOL			key_down(int type,
		const EmscriptenKeyboardEvent *key, void *data);
EM_BOOL			key_up(int type,
		const EmscriptenKeyboardEvent *key, void *data);
void			handle_input(t_scop *scop);
void			validate_shader(GLuint shader);
GLuint			compile_shader(const char *path, GLenum shader_type);
void			validate_program(GLuint program_id);
GLuint			make_program(const char *frag, const char *vert);

#endif
