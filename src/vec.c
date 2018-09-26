/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:44:27 by lkaser            #+#    #+#             */
/*   Updated: 2018/02/13 17:34:06 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include <math.h>

t_vec3	vec3_x_mat(t_vec3 v, t_mat *m)
{
	t_vec3	r;
	float	w;

	r.x = v.x * m->m[0][0] + v.y * m->m[1][0] + v.z * m->m[2][0] + m->m[3][0];
	r.y = v.x * m->m[0][1] + v.y * m->m[1][1] + v.z * m->m[2][1] + m->m[3][1];
	r.z = v.x * m->m[0][2] + v.y * m->m[1][2] + v.z * m->m[2][2] + m->m[3][2];
	w = v.x * m->m[0][3] + v.y * m->m[1][3] + v.z * m->m[2][3] + m->m[3][3];
	if (w != 1 && w)
	{
		r.x /= w;
		r.y /= w;
		r.z /= w;
	}
	return (r);
}

t_vec3	dir3_x_mat(t_vec3 v, t_mat *m)
{
	t_vec3	r;

	r.x = v.x * m->m[0][0] + v.y * m->m[1][0] + v.z * m->m[2][0];
	r.y = v.x * m->m[0][1] + v.y * m->m[1][1] + v.z * m->m[2][1];
	r.z = v.x * m->m[0][2] + v.y * m->m[1][2] + v.z * m->m[2][2];
	return (r);
}

float	vec3_length(t_vec3 *v)
{
	return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}

void	vec3_normalize(t_vec3 *v)
{
	float len;

	len = v->x * v->x + v->y * v->y + v->z * v->z;
	if (len > 0)
	{
		len = 1 / sqrt(len);
		v->x *= len;
		v->y *= len;
		v->z *= len;
	}
}

t_vec3	vec3_cross_product(t_vec3 a, t_vec3 b)
{
	return (V3(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x));
}
