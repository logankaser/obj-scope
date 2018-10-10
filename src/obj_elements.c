#include <stdlib.h>
#include <string.h>
#include "obj.h"
#include "matrix.h"

#define TRIANGLE i, i+1, i+2, i+3, i+4, i+5, i+6, i+7, i+8

void	obj_load(FILE *obj_file,
	t_uvector *vert, t_uvector *uv, t_uvector *norm)
{
	t_uvector	raw_vert;
	t_uvector	raw_uv;
	t_uvector	raw_norm;
	char		*line;
	int	i[9];

	line = obj_read(obj_file, &raw_vert, &raw_uv, &raw_norm);
	while (read_line(obj_file, &line) > 0)
	{
		if (strncmp(line, "f ", 2))
			continue;
		sscanf(line, "f %i/%i/%i %i/%i/%i %i/%i/%i\n", TRIANGLE);
		ft_uvector_push(vert, ft_uvector_get(&raw_vert, i[0] - 1, 0));
		ft_uvector_push(uv, ft_uvector_get(&raw_uv, i[1] - 1, 0));
		ft_uvector_push(norm, ft_uvector_get(&raw_norm, i[2] - 1, 0));
		
		ft_uvector_push(vert, ft_uvector_get(&raw_vert, i[3] - 1, 0));
		ft_uvector_push(uv, ft_uvector_get(&raw_uv, i[4] - 1, 0));
		ft_uvector_push(norm, ft_uvector_get(&raw_norm, i[5] - 1, 0));

		ft_uvector_push(vert, ft_uvector_get(&raw_vert, i[6] - 1, 0));
		ft_uvector_push(uv, ft_uvector_get(&raw_uv, i[7] - 1, 0));
		ft_uvector_push(norm, ft_uvector_get(&raw_norm, i[8] - 1, 0));
	}
	free(raw_vert.data);
	free(raw_uv.data);
	free(raw_norm.data);
}


void	obj_normalize(t_uvector *vert, t_uvector *uv, t_uvector *norm)
{
	unsigned	i;
	t_vec3		*v;
	t_vec2		max;
	t_vec3		avg;

	i = 0;
	max.x = 0.0f;
	(void)uv;
	(void)norm;
	while (i < vert->length)
	{
		v = ft_uvector_get(vert, i++, 0);
		if ((max.y = vec3_length(v)) > max.x)
			max.x = max.y;
		vec3_plus_vec3(&avg, v);
	}
	vec3_div(&avg, vert->length);
	max.x -= vec3_length(&avg);
	i = 0;
	while (i < vert->length)
	{
		v = ft_uvector_get(vert, i++, 0);
		vec3_minus_vec3(v, &avg);
		vec3_div(v, max.x);
	}
}
