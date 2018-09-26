#include <stdlib.h>
#include <string.h>
#include "obj.h"

#define TRIANGLE i, i+3, i+6, i+1, i+4, i+7, i+2, i+5, i+8

void		load_obj(FILE *obj_file,
	t_uvector *vert, t_uvector *uv, t_uvector *norm)
{
	t_uvector	raw_vert;
	t_uvector	raw_uv;
	t_uvector	raw_norm;
	char		*line;
	unsigned	i[9];

	line = read_obj(obj_file, &raw_vert, &raw_uv, &raw_norm);
	while (read_line(obj_file, &line) > 0)
	{
		if (!strncmp(line, "#", 1) || strncmp(line, "f ", 2))
			continue;
		sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d\n", TRIANGLE);
		ft_uvector_push(vert, ft_uvector_get(&raw_vert, i[0] - 1, 0));
		ft_uvector_push(vert, ft_uvector_get(&raw_vert, i[1] - 1, 0));
		ft_uvector_push(vert, ft_uvector_get(&raw_vert, i[2] - 1, 0));
		ft_uvector_push(uv, ft_uvector_get(&raw_uv, i[3] - 1, 0));
		ft_uvector_push(uv, ft_uvector_get(&raw_uv, i[4] - 1, 0));
		ft_uvector_push(uv, ft_uvector_get(&raw_uv, i[5] - 1, 0));
		ft_uvector_push(norm, ft_uvector_get(&raw_norm, i[6] - 1, 0));
		ft_uvector_push(norm, ft_uvector_get(&raw_norm, i[7] - 1, 0));
		ft_uvector_push(norm, ft_uvector_get(&raw_norm, i[8] - 1, 0));
	}
	free(raw_vert.data);
	free(raw_uv.data);
	free(raw_norm.data);
}
