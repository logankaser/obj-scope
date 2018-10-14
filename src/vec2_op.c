/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:44:27 by lkaser            #+#    #+#             */
/*   Updated: 2018/10/13 17:40:38 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include <math.h>

void	vec2_minus_vec2(t_vec2 *a, t_vec2 *b)
{
	a->x -= b->x;
	a->y -= b->y;
}

void	vec2_plus_vec2(t_vec2 *a, t_vec2 *b)
{
	a->x += b->x;
	a->y += b->y;
}

void	vec2_mult(t_vec2 *v, float m)
{
	v->x *= m;
	v->y *= m;
}

void	vec2_div(t_vec2 *v, float d)
{
	v->x /= d;
	v->y /= d;
}

float	vec2_dot(t_vec2 *a, t_vec2 *b)
{
	return (a->x * b->x + a->y * b->y);
}
