/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 17:40:29 by lkaser            #+#    #+#             */
/*   Updated: 2018/10/13 17:40:31 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	uv_or_gen(t_uvector *uv,
	t_uvector *vertexs, unsigned *face, t_vec3 *avg)
{
	t_vec3 pos;
	t_vec3 tmp;
	t_vec2 gen_uv;

	if (face[1] - 1 < vertexs[1].length)
		ft_uvector_push(uv, ft_uvector_get(vertexs + 1, face[1] - 1));
	else
	{
		pos = *((t_vec3*)ft_uvector_get(vertexs, face[0] - 1));
		vec3_minus_vec3(&pos, avg);
		vec3_normalize(&pos);
		tmp = V3(1.0f, 0.0f, 0.0f);
		gen_uv.x = -acosf(vec3_dot(&pos, &tmp));
		tmp = V3(0.0f, 1.0f, 0.0f);
		gen_uv.y = acosf(vec3_dot(&pos, &tmp));
		vec2_div(&gen_uv, M_PI);
		ft_uvector_push(uv, &gen_uv);
	}
}

static void	norm_or_gen(t_uvector *norm,
	t_uvector *vertexs, unsigned *face, t_vec3 *avg)
{
	if (face[2] - 1 < vertexs[2].length)
		ft_uvector_push(norm, ft_uvector_get(vertexs + 2, face[2] - 1));
	else
	{
		ft_uvector_push(norm, ft_uvector_get(vertexs, face[0] - 1));
		vec3_minus_vec3(ft_uvector_get(norm, norm->length - 1), avg);
	}
}

void		obj_load(FILE *obj_file,
	t_uvector *vert, t_uvector *uv, t_uvector *norm)
{
	t_uvector	vertexs[3];
	t_uvector	faces;
	unsigned	*face;
	unsigned	i;
	t_vec3		avg;

	ft_uvector_init(vert, sizeof(t_vec3));
	ft_uvector_init(uv, sizeof(t_vec2));
	ft_uvector_init(norm, sizeof(t_vec3));
	obj_parse(obj_file, vertexs, &faces);
	i = 0;
	while (i < vertexs->length)
		vec3_plus_vec3(&avg, ft_uvector_get(vertexs, i++));
	vec3_div(&avg, vertexs->length);
	i = 0;
	while ((face = ft_uvector_get(&faces, i++)))
	{
		ft_uvector_push(vert, ft_uvector_get(vertexs, face[0] - 1));
		uv_or_gen(uv, vertexs, face, &avg);
		norm_or_gen(norm, vertexs, face, &avg);
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
