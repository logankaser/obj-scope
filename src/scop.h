#ifndef SCOP_H
# define SCOP_H
# include <GLES3/gl3.h>
# include "matrix.h"

typedef struct		s_scop
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
}					t_scop;

#endif