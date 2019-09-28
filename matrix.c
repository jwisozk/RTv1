/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iplastun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:12:01 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/24 19:44:26 by iplastun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	ft_fill_tmp(double *a, double *b, double a_, double b_)
{
	*a = a_;
	*b = b_;
}

//t_vec3 *ft_rotate(t_vec3 *v, t_ang3 *a)
//{
//	double	x;
//	double	y;
//	double	z;
//
//	ft_fill_tmp(&x, &z, v->x, v->z);
//	if (a->y)
//	{
//		v->x = x * COS(a->y) - z * SIN(a->y);
//		v->z = x * SIN(a->y) + z * COS(a->y);
//	}
//	ft_fill_tmp(&y, &z, v->y, v->z);
//	if (a->x)
//	{
//		v->y = y * COS(a->x) - z * SIN(a->x);
//		v->z = y * SIN(a->x) + z * COS(a->x);
//	}
//
//	ft_fill_tmp(&x, &y, v->x, v->y);
//	if (a->z)
//	{
//		v->x = x * COS(a->z) - y * SIN(a->z);
//		v->y = x * SIN(a->z) + y * COS(a->z);
//	}
//	return (v);
//}

t_vec3 *ft_rotate_x(t_vec3 *v, t_ang3 *a)
{

	double	y;
	double	z;

	ft_fill_tmp(&y, &z, v->y, v->z);
	if (a->x)
	{
		v->y = y * COS(a->x) - z * SIN(a->x);
		v->z = y * SIN(a->x) + z * COS(a->x);
	}

	return (v);
}
t_vec3 *ft_rotate_y(t_vec3 *v, t_ang3 *a)
{
	double	x;

	double	z;

	ft_fill_tmp(&x, &z, v->x, v->z);
	if (a->y)
	{
		v->x = x * COS(a->y) - z * SIN(a->y);
		v->z = x * SIN(a->y) + z * COS(a->y);
	}
	return (v);
}

t_vec3 *ft_rotate_z(t_vec3 *v, t_ang3 *a)
{
	double	x;
	double	y;

	ft_fill_tmp(&x, &y, v->x, v->y);
	if (a->z)
	{
		v->x = x * COS(a->z) - y * SIN(a->z);
		v->y = x * SIN(a->z) + y * COS(a->z);
	}
	return (v);
}


t_vec4	*ft_create_vec4(double x, double y, double z)
{
	t_vec4 *p;

	p = (t_vec4*)malloc(sizeof(t_vec4));
	p->x = x;
	p->y = y;
	p->z = z;
	p->k = 1;
	return (p);
}

double **ft_create_double_ptr()
{
	double **c = (double**)malloc(sizeof(double*) * 4);
	int i = 0;
	while (i < 4)
	{
		c[i] = (double*)malloc(sizeof(double) * 4);
		i++;
	}
	return (c);
}

double **ft_matrix_product(double **a, double **b)
{
	double **c;

	c = ft_create_double_ptr();

//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			c[i][j] += a[i][j] * b[j][i];
//		}
//	}

	c[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0] + a[0][2] * b[2][0] + a[0][3] * b[3][0];
	c[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1] + a[0][2] * b[2][1] + a[0][3] * b[3][1];
	c[0][2] = a[0][0] * b[0][2] + a[0][1] * b[1][2] + a[0][2] * b[2][2] + a[0][3] * b[3][2];
	c[0][3] = a[0][0] * b[0][3] + a[0][1] * b[1][3] + a[0][2] * b[2][3] + a[0][3] * b[3][3];

	c[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0] + a[1][2] * b[2][0] + a[1][3] * b[3][0];
	c[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1] + a[1][2] * b[2][1] + a[1][3] * b[3][1];
	c[1][2] = a[1][0] * b[0][2] + a[1][1] * b[1][2] + a[1][2] * b[2][2] + a[1][3] * b[3][2];
	c[1][3] = a[1][0] * b[0][3] + a[1][1] * b[1][3] + a[1][2] * b[2][3] + a[1][3] * b[3][3];

	c[2][0] = a[2][0] * b[0][0] + a[2][1] * b[1][0] + a[2][2] * b[2][0] + a[2][3] * b[3][0];
	c[2][1] = a[2][0] * b[0][1] + a[2][1] * b[1][1] + a[2][2] * b[2][1] + a[2][3] * b[3][1];
	c[2][2] = a[2][0] * b[0][2] + a[2][1] * b[1][2] + a[2][2] * b[2][2] + a[2][3] * b[3][2];
	c[2][3] = a[2][0] * b[0][3] + a[2][1] * b[1][3] + a[2][2] * b[2][3] + a[2][3] * b[3][3];

	c[3][0] = a[3][0] * b[0][0] + a[3][1] * b[1][0] + a[3][2] * b[2][0] + a[3][3] * b[3][0];
	c[3][1] = a[3][0] * b[0][1] + a[3][1] * b[1][1] + a[3][2] * b[2][1] + a[3][3] * b[3][1];
	c[3][2] = a[3][0] * b[0][2] + a[3][1] * b[1][2] + a[3][2] * b[2][2] + a[3][3] * b[3][2];
	c[3][3] = a[3][0] * b[0][3] + a[3][1] * b[1][3] + a[3][2] * b[2][3] + a[3][3] * b[3][3];

	return (c);
}

t_vec3 *ft_product_mv(double **c, t_vec4 *nd)
{
//	var MultiplyMV = function(mat, vec) {
//		t_vec4 *result = ft_create_vec4(0,0,0);
		double result[4] = {0,0,0,0};

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (j == 0)
					result[i] += nd->x * c[i][j];
				if (j == 1)
					result[i] += nd->y * c[i][j];
				if (j == 2)
					result[i] += nd->z * c[i][j];
				if (j == 3)
					result[i] += nd->k * c[i][j];
			}
		}

//		result[0] = nd->x * c[0][0] + nd->y * c[1][0] + nd->z * c[2][0] + nd->k * 0;
//		result[1] = nd->x * c[0][1] + nd->y * c[1][1] + nd->z * c[2][1] + nd->k * 0;
//		result[2] = nd->x * c[0][2] + nd->y * c[1][2] + nd->z * c[2][2] + nd->k * 0;
//		result[3] = nd->x * c[0][3] + nd->y * c[1][3] + nd->z * c[2][3] + c[3][3];
//		if (result[3] != 1 && result[3] != 0) {
//			result[0] = result[0] / result[3];
//			result[1] = result[1] / result[3];
//			result[2] = result[2] / result[3];
//	}
	return (ft_create_vec3(result[0], result[1], result[2]));
}

//position 0 -2 15
//look_at 0 0 0

//t_camera create_camera(t_vec4 position, t_vec4 lookat, double fl)
//{
//    t_camera camera;
//    t_vec4 forward;
//    t_vec4 world_up;
//
//    camera.position = position;
//    camera.lookat = lookat;
//    world_up = create_vector(0, 1, 0);
//
//    forward = normalize( vector_sub(camera.lookat, camera.position) );
//    camera.left = normalize( cross_product(world_up, forward) );
//    camera.up = normalize( cross_product(forward, camera.left) );
//    camera.forward = forward;
//
//    camera.focal_length = fl;
//    camera.frame_height = 1;
//    camera.frame_width = 1;
//    return (camera);
//}
//x * data->view_w * data->dwi, -y * data->view_h * data->dhi, ZA);



//	double **m = ft_create_double_ptr();
//
//	m[0][0] = 1;
//	m[0][1] = 0;
//	m[0][2] = 0;
//	m[0][3] = -cam_pos->x;
//	m[1][0] = 0;
//	m[1][1] = 1;
//	m[1][2] = 0;
//	m[1][3] = -cam_pos->y;
//	m[2][0] = 0;
//	m[2][1] = 0;
//	m[2][2] = 1;
//	m[2][3] = -cam_pos->z;
//	m[3][0] = 0;
//	m[3][1] = 0;
//	m[3][2] = 0;
//	m[3][3] = 1;
//
//	double **camToWorld = ft_create_double_ptr();
//	camToWorld[0][0] = right->x;
//	camToWorld[0][1] = right->y;
//	camToWorld[0][2] = right->z;
//	camToWorld[0][3] = 0;
//	camToWorld[1][0] = up->x;
//	camToWorld[1][1] = up->y;
//	camToWorld[1][2] = up->z;
//	camToWorld[1][3] = 0;
//	camToWorld[2][0] = forward->x;
//	camToWorld[2][1] = forward->y;
//	camToWorld[2][2] = forward->z;
//	camToWorld[2][3] = 0;
//	camToWorld[3][0] = 0;
//	camToWorld[3][1] = 0;
//	camToWorld[3][2] = 0;
//	camToWorld[3][3] = 1;
//
//
//	double **c = ft_matrix_product(camToWorld, m);
//
////		int i = 0;
////		while (i < 4)
////		{
////			int j = 0;
////			while (j < 4)
////			{
////				printf("%f ", c[i][j]);
////				j++;
////			}
////			printf("\n");
////			i++;
////		}
//
////
////	exit(0);
//
//
//
////	camToWorld[3][0] = cam_pos->x;
////	camToWorld[3][1] = cam_pos->y;
////	camToWorld[3][2] = cam_pos->z;
//
//	t_vec4 *nd = ft_create_vec4(dir->x, dir->y, dir->z);
//
//	t_vec3 *p = ft_product_mv(c, nd);
//
//
//	return (p);
//}


