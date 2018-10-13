#include <stdlib.h>
#include <string.h>
#include "obj.h"
#include "matrix.h"

#define TRIANGLE i, i+1, i+2, i+3, i+4, i+5, i+6, i+7, i+8

void	obj_read_face(t_uvector *vert, t_uvector *uv, t_uvector *norm)
{
	(void)vert;
	(void)uv;
	(void)norm;
}

void	obj_load(FILE *obj_file,
	t_uvector *vert, t_uvector *uv, t_uvector *norm)
{
	t_uvector	vertexs[3];
	t_uvector	faces;
	int			*tmp;

	(void)uv;
	(void)norm;

	t_vec2 uv_default;
	t_vec3 norm_default;

	uv_default = V2(0, 0);
	norm_default = V3(0, 0, 0);

	obj_read(obj_file, vertexs, &faces);
	for (unsigned i = 0; i < faces.length; ++i)
	{
		tmp = ft_uvector_get(&faces, i, 0);
		ft_uvector_push(vert, ft_uvector_get(vertexs, tmp[0] - 1, 0));
		//ft_uvector_push(uv, ft_uvector_get(vertexs, tmp[1] - 1, 0));
		//ft_uvector_push(norm, ft_uvector_get(vertexs, tmp[2] - 1, 0));
		ft_uvector_push(uv, &uv_default);
		ft_uvector_push(norm, &norm_default);
	}
	free(vertexs[0].data);
	free(vertexs[1].data);
	free(vertexs[2].data);
	free(faces.data);
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