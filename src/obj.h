#ifndef OBJ_H
# define OBJ_H
# include <stdio.h>
# include "uvector.h"

int			read_line(FILE *file, char **line);

void		*obj_read(FILE *obj_file,
	t_uvector *raw_vert, t_uvector *raw_uv, t_uvector *raw_norm);

void		obj_load(FILE *obj_file,
	t_uvector *vert, t_uvector *uv, t_uvector *norm);

void		obj_normalize(
	t_uvector *raw_vert, t_uvector *raw_uv, t_uvector *raw_norm);

#endif