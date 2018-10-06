/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:44:27 by lkaser            #+#    #+#             */
/*   Updated: 2018/01/22 14:49:46 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

t_mat		*mat_new(int order, char id)
{
	t_mat	*new;
	int		i;
	int		j;

	new = malloc(sizeof(t_mat));
	new->order = order;
	i = -1;
	while (++i < order)
	{
		j = -1;
		while (++j < order)
			new->m[i][j] = i == j && id;
	}
	return (new);
}

void		mat_del(t_mat *m)
{
	int		i;

	i = -1;
	while (++i < m->order)
		free(m->m[i]);
	free(m->m);
	free(m);
}

t_mat		*mat_x_mat(const t_mat *b, const t_mat *a)
{
	int			i;
	int			j;
	int			k;
	int			order;
	t_mat		*product;

	if (a->order != b->order)
		return (NULL);
	order = a->order;
	product = mat_new(order, 0);
	i = -1;
	while (++i < order)
	{
		j = -1;
		while (++j < order)
		{
			k = -1;
			while (++k < order)
				product->m[i][j] += a->m[i][k] * b->m[k][j];
		}
	}
	return (product);
}

void		mat_x_mat_res(const t_mat *b, const t_mat *a, t_mat *product)
{
	int			i;
	int			j;
	int			k;
	int			order;

	bzero(&product->m, sizeof(float) * 4 * 4);
	order = product->order;
	i = -1;
	while (++i < order)
	{
		j = -1;
		while (++j < order)
		{
			k = -1;
			while (++k < order)
				product->m[i][j] += a->m[i][k] * b->m[k][j];
		}
	}
}

static void	mat_reduce(float tmp[4][8], int pivot, int order)
{
	int		i;
	int		j;
	float	factor;

	factor = tmp[pivot][pivot];
	i = -1;
	while (++i < order * 2)
		tmp[pivot][i] /= factor;
	i = -1;
	while (++i < order)
		if (i != pivot)
		{
			factor = tmp[i][pivot];
			j = -1;
			while (++j < order * 2)
				tmp[i][j] = tmp[i][j] - tmp[pivot][j] * factor;
		}
}

/*
** !Only works for square matrix of order 4 and lower.
*/

void		mat_inverse(const t_mat *m, t_mat *r)
{
	float	tmp[4][8];
	int		i;
	int		j;

	i = -1;
	while (++i < m->order)
	{
		j = -1;
		while (++j < m->order * 2)
			tmp[i][j] = j < m->order ? m->m[i][j] : j == i + m->order;
	}
	i = -1;
	while (++i < m->order)
		mat_reduce(tmp, i, m->order);
	i = -1;
	while (++i < m->order)
	{
		j = -1;
		while (++j < m->order)
			r->m[i][j] = tmp[i][j + m->order];
	}
}
