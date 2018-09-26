#ifndef SCOP_H
# define SCOP_H
# include <GLES3/gl3.h>
# include "matrix.h"

typedef struct		s_scop
{
	GLuint			mvp_id;
	GLuint			vao_id;
	t_mat			camera;
	unsigned		vert_count;
}					t_scop;

#endif