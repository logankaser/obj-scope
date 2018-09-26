/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 17:13:31 by lkaser            #+#    #+#             */
/*   Updated: 2018/02/03 15:25:51 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

void	look_at(t_vec3 from, t_vec3 to, t_mat *cam)
{
	t_vec3 forward;
	t_vec3 right;
	t_vec3 up;

	forward = V3_MINUS_V3(from, to);
	vec3_normalize(&forward);
	right = vec3_cross_product(V3(0, 1, 0), forward);
	up = vec3_cross_product(forward, right);
	MAT_ROW(cam->m[0], right.x, right.y, right.z, 0);
	MAT_ROW(cam->m[1], up.x, up.y, up.z, 0);
	MAT_ROW(cam->m[2], forward.x, forward.y, forward.z, 0);
	MAT_ROW(cam->m[3], from.x, from.y, from.z, 1);
}
