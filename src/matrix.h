/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 11:03:56 by lkaser            #+#    #+#             */
/*   Updated: 2018/02/15 21:06:56 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include <math.h>
# define RGB(r,g,b) ((b) + ((g) << 8) + ((r) << 16))
# define V2(x,y) ((t_vec2){x,y})
# define V3(x,y,z) ((t_vec3){x,y,z})
# define V3_MINUS_V3(a,b) (V3(a.x - b.x, a.y - b.y, a.z - b.z))
# define V3_PLUS_V3(a,b) (V3(a.x + b.x, a.y + b.y, a.z + b.z))
# define V3_MULT(v, m) (V3(v.x * m, v.y * m, v.z * m))
# define V3_DIV(v, d) (V3(v.x / d, v.y / d, v.z / d))
# define V3_DOT(a,b) (a.x * b.x + a.y * b.y + a.z * b.z)
# define MAT_ROW(m,x,y,z,w) m[0] = x;m[1] = y;m[2] = z;m[3] = w

typedef struct		s_vec2
{
	float			x;
	float			y;
}					t_vec2;

typedef struct		s_vec3
{
	float			x;
	float			y;
	float			z;
}					t_vec3;

typedef struct		s_mat
{
	int				order;
	float			m[4][4];
}					t_mat;

t_mat				*mat_new(int order, char id);
void				mat_del(t_mat *m);
t_mat				*mat_x_mat(const t_mat *a, const t_mat *b);
void				mat_x_mat_res(
	const t_mat *b, const t_mat *a, t_mat *product);
void				mat_inverse(const t_mat *m, t_mat *r);

t_vec3				vec3_x_mat(t_vec3 v, t_mat *m);
t_vec3				dir3_x_mat(t_vec3 v, t_mat *m);
float				vec3_length(t_vec3 *v);
void				vec3_normalize(t_vec3 *v);
t_vec3				vec3_cross_product(t_vec3 a, t_vec3 b);

void				vec3_minus_vec3(t_vec3 *a, t_vec3 *b);
void				vec3_plus_vec3(t_vec3 *a, t_vec3 *b);
void				vec3_mult(t_vec3 *v, float m);
void				vec3_div(t_vec3 *v, float d);
float				vec3_dot(t_vec3 *a, t_vec3 *b);

void				look_at(t_vec3 from, t_vec3 to, t_mat *cam);

#endif
