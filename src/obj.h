/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 19:39:12 by lkaser            #+#    #+#             */
/*   Updated: 2018/10/13 19:39:14 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
# define OBJ_H
# include <stdio.h>
# include "uvector.h"

void		obj_load(FILE *obj_file,
	t_uvector *vert, t_uvector *uv, t_uvector *norm);

void		obj_normalize(t_uvector *raw_vert);

/*
** Internal functions.
*/

void		parse_vertex(const char *line, t_uvector *out);
void		parse_uv(const char *line, t_uvector *out);
void		parse_normal(const char *line, t_uvector *out);
void		parse_face(char *line, t_uvector *faces, t_uvector vertex[3]);

#endif
