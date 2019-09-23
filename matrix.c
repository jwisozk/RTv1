/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:12:01 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/21 21:11:27 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	ft_fill_tmp(double *a, double *b, double a_, double b_)
{
	*a = a_;
	*b = b_;
}

t_vec3 *ft_rotate(t_vec3 *v, t_ang3 *a)
{
	double	x;
	double	y;
	double	z;

	ft_fill_tmp(&y, &z, v->y, v->z);
	if (a->x)
	{
		v->y = y * COS(a->x) - z * SIN(a->x);
		v->z = y * SIN(a->x) + z * COS(a->x);
	}
	ft_fill_tmp(&x, &z, v->x, v->z);
	if (a->y)
	{
		v->x = x * COS(a->y) - z * SIN(a->y);
		v->z = x * SIN(a->y) + z * COS(a->y);
	}
	ft_fill_tmp(&x, &y, v->x, v->y);
	if (a->z)
	{
		v->x = x * COS(a->z) - y * SIN(a->z);
		v->y = x * SIN(a->z) + y * COS(a->z);
	}
	return (v);
}

t_vec3 *ft_translate(t_vec3* o, t_vec3* t)
{
	o->x += t->x;
	o->y += t->y;
	o->z += t->z;
	return (o);
}

t_vec3 *ft_camera_look_at(t_vec3 *cam_pos)
{
	t_vec3 *origin;
	t_vec3 *forward;
	t_vec3 *right;
	t_vec3 *up;

	origin = ft_create_vec3(0,0,0);
	forward = ft_normalize_vec3(ft_subtract(cam_pos, origin));
	right = ft_cross_product(ft_create_vec3(0,1,0), forward);
	up = ft_cross_product(forward, right);
	return (up);
}