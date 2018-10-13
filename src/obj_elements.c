#include <stdlib.h>
#include <string.h>
#include "obj.h"
#include "matrix.h"

static void	obj_parse(FILE *obj_file, t_uvector vertex[3], t_uvector *faces)
{
	char	*line;
	size_t	n;

	ft_uvector_init(vertex, sizeof(t_vec3));
	ft_uvector_init(vertex + 1, sizeof(t_vec2));
	ft_uvector_init(vertex + 2, sizeof(t_vec3));
	ft_uvector_init(faces, sizeof(int) * 3);
	line = NULL;
	while (getline(&line, &n, obj_file) > 0)
	{
		if (!strncmp(line, "v ", 2))
			parse_vertex(line, vertex);
		else if (!strncmp(line, "vt ", 3))
			parse_uv(line, vertex + 1);
		else if (!strncmp(line, "vn ", 3))
			parse_normal(line, vertex + 2);
		else if (!strncmp(line, "f ", 2))
			parse_face(line + 1, faces, vertex);
		free(line);
		line = NULL;
	}
}

static void uv_or_gen(t_uvector *uv, t_uvector *vertexs, unsigned *tmp)
{
	if (tmp[1] - 1 < vertexs[1].length)
		ft_uvector_push(uv, ft_uvector_get(vertexs + 1, tmp[1] - 1));
	else
	{
		t_vec2 uv_def;
		uv_def = V2(0.0, 0.0);
		ft_uvector_push(uv, &uv_def);
	}
}

static void	norm_or_gen(t_uvector *norm, 
	t_uvector *vertexs, unsigned *tmp, t_vec3 *avg)
{
	if (tmp[2] - 1 < vertexs[2].length)
		ft_uvector_push(norm, ft_uvector_get(vertexs + 2, tmp[2] - 1));
	else
	{
		ft_uvector_push(norm, ft_uvector_get(vertexs, tmp[0] - 1));
		vec3_minus_vec3(ft_uvector_get(norm, norm->length - 1), avg);
	}
}

void		obj_load(FILE *obj_file,
	t_uvector *vert, t_uvector *uv, t_uvector *norm)
{
	t_uvector	vertexs[3];
	t_uvector	faces;
	unsigned	*tmp;
	unsigned	i;
	t_vec3		avg;

	obj_parse(obj_file, vertexs, &faces);
	i = 0;
	while (i < vertexs->length)
		vec3_plus_vec3(&avg, ft_uvector_get(vertexs, i++));
	vec3_div(&avg, vertexs->length);
	i = 0;
	while (i < faces.length)
	{
		tmp = ft_uvector_get(&faces, i++);
		ft_uvector_push(vert, ft_uvector_get(vertexs, tmp[0] - 1));
		uv_or_gen(uv, vertexs, tmp);
		norm_or_gen(norm, vertexs, tmp, &avg);
	}
	free(vertexs[0].data);
	free(vertexs[1].data);
	free(vertexs[2].data);
	free(faces.data);
}

void		obj_normalize(t_uvector *vert)
{
	unsigned	i;
	t_vec3		*v;
	t_vec2		max;
	t_vec3		avg;

	i = 0;
	max.x = 0.0f;
	while (i < vert->length)
	{
		v = ft_uvector_get(vert, i++);
		if ((max.y = vec3_length(v)) > max.x)
			max.x = max.y;
		vec3_plus_vec3(&avg, v);
	}
	vec3_div(&avg, vert->length);
	max.x -= vec3_length(&avg);
	i = 0;
	while (i < vert->length)
	{
		v = ft_uvector_get(vert, i++);
		vec3_minus_vec3(v, &avg);
		vec3_div(v, max.x);
	}
}