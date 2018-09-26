/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:44:27 by lkaser            #+#    #+#             */
/*   Updated: 2018/02/15 21:08:44 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include <math.h>

void	vec3_minus_vec3(t_vec3 *a, t_vec3 *b)
{
	a->x -= b->x;
	a->y -= b->y;
	a->z -= b->z;
}

void	vec3_plus_vec3(t_vec3 *a, t_vec3 *b)
{
	a->x += b->x;
	a->y += b->y;
	a->z += b->z;
}

void	vec3_mult(t_vec3 *v, float m)
{
	v->x *= m;
	v->y *= m;
	v->z *= m;
}

void	vec3_div(t_vec3 *v, float d)
{
	v->x /= d;
	v->y /= d;
	v->z /= d;
}

float	vec3_dot(t_vec3 *a, t_vec3 *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}
