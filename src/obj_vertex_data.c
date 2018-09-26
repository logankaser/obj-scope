#include <stdlib.h>
#include <string.h>
#include "obj.h"
#include "matrix.h"

static void	parse_vertex(const char *line, t_uvector *out)
{
	t_vec3	tmp;

	tmp = V3(0.0f, 0.0f, 0.0f);
	sscanf(line, "v %f %f %f\n", &tmp.x, &tmp.y, &tmp.z);
	ft_uvector_push(out, &tmp);
}

static void	parse_uv(const char *line, t_uvector *out)
{
	t_vec2	tmp;

	tmp = V2(0.0f, 0.0f);
	sscanf(line, "vt %f %f\n", &tmp.x, &tmp.y);
	ft_uvector_push(out, &tmp);
}

static void	parse_normal(const char *line, t_uvector *out)
{
	t_vec3	tmp;

	tmp = V3(0.0f, 0.0f, 0.0f);
	sscanf(line, "vn %f %f %f\n", &tmp.x, &tmp.y, &tmp.z);
	ft_uvector_push(out, &tmp);
}

int			read_line(FILE *file, char **line)
{
	size_t n;

	free(*line);
	*line = NULL;
	return (getline(line, &n, file));
}

void		*read_obj(FILE *obj_file,
	t_uvector *raw_vert, t_uvector *raw_uv, t_uvector *raw_norm)
{
	char	*line;

	ft_uvector_init(raw_vert, sizeof(t_vec3));
	ft_uvector_init(raw_uv, sizeof(t_vec2));
	ft_uvector_init(raw_norm, sizeof(t_vec3));
	line = NULL;
	while (read_line(obj_file, &line) > 0)
	{
		if (!strncmp(line, "#", 1))
			continue ; 
		if (!strncmp(line, "f ", 2))
			break ;
		if (!strncmp(line, "v ", 2))
			parse_vertex(line, raw_vert);
		else if (!strncmp(line, "vt ", 3))
			parse_uv(line, raw_uv);
		else if (!strncmp(line, "vn ", 3))
			parse_normal(line, raw_norm);
	}
	return (NULL);
}