/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_vertex_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 11:58:07 by lkaser            #+#    #+#             */
/*   Updated: 2018/08/02 12:00:07 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "obj.h"
#include "matrix.h"

void		parse_vertex(const char *line, t_uvector *out)
{
	t_vec3	tmp;

	tmp = V3(0.0f, 0.0f, 0.0f);
	sscanf(line, "v %f %f %f\n", &tmp.x, &tmp.y, &tmp.z);
	ft_uvector_push(out, &tmp);
}

void		parse_uv(const char *line, t_uvector *out)
{
	t_vec2	tmp;

	tmp = V2(0.0f, 0.0f);
	sscanf(line, "vt %f %f\n", &tmp.x, &tmp.y);
	ft_uvector_push(out, &tmp);
}

void		parse_normal(const char *line, t_uvector *out)
{
	t_vec3	tmp;

	tmp = V3(0.0f, 0.0f, 0.0f);
	sscanf(line, "vn %f %f %f\n", &tmp.x, &tmp.y, &tmp.z);
	ft_uvector_push(out, &tmp);
}

void		trianglate(t_uvector *faces)
{
	ft_uvector_push(faces, ft_uvector_get(faces, faces->length - 2, 0));
	ft_uvector_push(faces, ft_uvector_get(faces, faces->length - 5, 0));
}

/*
** The face forms supported by this function are:
** f 1 1 1
** f 1/1 1/1 1/1
** f 1//1 1//1 1//1
** f 1/1/1 1/1/1 1/1/1
** Or any of these with an extra vertex in which case it will be trianglized.
*/

#define VCOUNT i[3]

static void	parse_face(char *line, t_uvector *faces, t_uvector vertex[3])
{
	char		*tok;
	char		*tok_save;
	int			i[4];

	VCOUNT = 0;
	tok = strtok_r(line, " \n", &tok_save);
	while (tok && VCOUNT <= 4)
	{
		bzero(i, sizeof(int) * 3);
		if (!((sscanf(tok, "%i/%i/%i", i, i + 1, i + 2) == 3)
			|| (sscanf(tok, "%i/%i", i, i + 1) == 2)
			|| (sscanf(tok, "%i//%i", i, i + 2) == 2)
			|| (sscanf(tok, "%i", i) == 1)))
			continue;
		if (i[0] < 0)
			i[0] = vertex[0].length + (i[0] + 1);
		if (i[1] < 0)
			i[1] = vertex[1].length + (i[1] + 1);
		if (i[2] < 0)
			i[2] = vertex[2].length + (i[2] + 1);
		ft_uvector_push(faces, i);
		if (++VCOUNT == 4)
			trianglate(faces);
		tok = strtok_r(NULL, " \n", &tok_save);
	}
}

/*
** fseek line is to allow the next parsing function to read from where
** this function stopped being able to parse, instead of losing that line
** vertex order is position, uv, normal.
*/

void		obj_read(FILE *obj_file, t_uvector vertex[3], t_uvector *faces)
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
