#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "matrix.h"

void matrix_print(t_mat *m)
{
	printf("%+.3f, %+.3f, %+.3f, %+.3f\n", m->m[0][0], m->m[0][1], m->m[0][2], m->m[0][3]);
	printf("%+.3f, %+.3f, %+.3f, %+.3f\n", m->m[1][0], m->m[1][1], m->m[1][2], m->m[1][3]);
	printf("%+.3f, %+.3f, %+.3f, %+.3f\n", m->m[2][0], m->m[2][1], m->m[2][2], m->m[2][3]);
	printf("%+.3f, %+.3f, %+.3f, %+.3f\n\n", m->m[3][0], m->m[3][1], m->m[3][2], m->m[3][3]);
}

void mat_translate(float x, float y, float z, t_mat *mat)
{
	t_mat	trans;
	t_mat	res;

	trans.order = 4;
	res.order = 4;
	MAT_ROW(trans.m[0], 1, 0, 0, 0);
	MAT_ROW(trans.m[1], 0, 1, 0, 0);
	MAT_ROW(trans.m[2], 0, 0, 1, 0);
	MAT_ROW(trans.m[3], x, y, z, 1);
	mat_x_mat_res(&trans, mat, &res);
	memcpy(&mat->m, &res.m, sizeof(float) * 16);
}

void mat_rotate_x(float degree, t_mat *mat)
{
	t_mat	rotate;
	t_mat	res;
	float	theta;

	theta = degree * 0.0174533;
	rotate.order = 4;
	res.order = 4;
	MAT_ROW(rotate.m[0], 1, 0, 0, 0);
	MAT_ROW(rotate.m[1], 0, cosf(theta), -sinf(theta), 0);
	MAT_ROW(rotate.m[2], 0, sinf(theta), cosf(theta), 0);
	MAT_ROW(rotate.m[3], 0, 0, 0, 1);
	mat_x_mat_res(&rotate, mat, &res);
	memcpy(&mat->m, &res.m, sizeof(float) * 16);
}

void mat_rotate_y(float degree, t_mat *mat)
{
	t_mat	rotate;
	t_mat	res;
	float	phi;

	phi = degree * 0.0174533;
	rotate.order = 4;
	res.order = 4;
	MAT_ROW(rotate.m[0], cosf(phi), 0, sinf(phi), 0);
	MAT_ROW(rotate.m[1], 0, 1, 0, 0);
	MAT_ROW(rotate.m[2], -sinf(phi), 0, cosf(phi), 0);
	MAT_ROW(rotate.m[3], 0, 0, 0, 1);
	mat_x_mat_res(&rotate, mat, &res);
	memcpy(&mat->m, &res.m, sizeof(float) * 16);
}

void mat_rotate_z(float degree, t_mat *mat)
{
	t_mat	rotate;
	t_mat	res;
	float	psi;

	psi = degree * 0.0174533;
	rotate.order = 4;
	res.order = 4;
	MAT_ROW(rotate.m[0], cosf(psi), -sinf(psi), 0, 0);
	MAT_ROW(rotate.m[1], sinf(psi), cosf(psi), 0, 0);
	MAT_ROW(rotate.m[2], 0, 0, 1, 0);
	MAT_ROW(rotate.m[3], 0, 0, 0, 1);
	mat_x_mat_res(&rotate, mat, &res);
	memcpy(&mat->m, &res.m, sizeof(float) * 16);
}

