#ifndef OBJ_H
# define OBJ_H
# include <stdio.h>
# include "uvector.h"

int			read_line(FILE *file, char **line);

void		*read_obj(FILE *obj_file,
	t_uvector *raw_vert, t_uvector *raw_uv, t_uvector *raw_norm);

void		load_obj(FILE *obj_file,
	t_uvector *vert, t_uvector *uv, t_uvector *norm);

#endif