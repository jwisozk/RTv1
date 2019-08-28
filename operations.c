/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:33:15 by jwisozk           #+#    #+#             */
/*   Updated: 2019/08/28 14:38:29 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

double ft_lenv(t_point *v)
{
	return sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
}

double ft_dot(t_point *v1, t_point *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_point *ft_multiply(double k, t_point *v)
{
	v->x *= k;
	v->y *= k;
	v->z *= k;
	return (v);
}

t_point *ft_add(t_point *v1, t_point *v2)
{
	t_point *p;
	p = ft_create_point(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z);
	return (p);
}

t_point *ft_subtract(t_point *v1, t_point *v2)
{
	t_point *p;
	p = ft_create_point(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
	return (p);
}

//double ft_length_vector(t_vector v)
//{
//	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
////	return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
//}
//
//t_vector ft_normalize_vector(t_vector v)
//{
//	double len;
//	double inv_len;
//
//	len = ft_length_vector(v);
//	if (len > 0)
//	{
//		inv_len = 1 / len;
//		v.x *= inv_len;
//		v.y *= inv_len;
//		v.z *= inv_len;
//	}
//	return (v);
//}

//O = <0, 0, 0>
//for x in [-Cw/2, Cw/2] {
//		for y in [-Ch/2, Ch/2] {
//			D = CanvasToview(x, y)
//			color = TraceRay(O, D, 1, inf)
//			canvas.PutPixel(x, y, color)
//		}
//}
