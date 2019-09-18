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

double ft_lenv(t_vec3 *v)
{
	return sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
}

double ft_dot(t_vec3 *v1, t_vec3 *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vec3 *ft_multiply(double k, t_vec3 *v)
{
	t_vec3* p;

	p = ft_create_vec3(v->x * k, v->y * k, v->z * k);
	return (p);
}

t_vec3 *ft_add(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3 *p;
	p = ft_create_vec3(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z);
	return (p);
}

t_vec3 *ft_subtract(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3 *p;
	p = ft_create_vec3(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
	return (p);
}

double ft_max(double x, double y)
{
    return (x > y ? x : y);
}

double ft_min(double x, double y)
{
    return (x < y ? x : y);
}

t_vec3 *ft_normalize_vec3(t_vec3 *v)
{
	double len;
	double inv_len;
	t_vec3 *nv;

	nv = ft_create_vec3(v->x, v->y, v->z);
	len = ft_lenv(v);
	if (len > 0)
	{
		inv_len = 1.0 / len;
		nv->x *= inv_len;
		nv->y *= inv_len;
		nv->z *= inv_len;
	}
	return (nv);
}
