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

t_vec3 *ft_rotate_y(t_vec3 *v, int d)
{
//	{{COS(d), SIN(d), 0},{-SIN(d), COS(d), 0},{0, 0, 1}};
//	static double m[] = {COS(d), 0, -SIN(d)};
//	double matrix_y[3][3] = {{COS(d), 0, -SIN(d)}, {0, 1, 0}, {SIN(d), 0, COS(d)}};

	double matrix_y[9] = {COS(d), 0, -SIN(d), 0, 1, 0, SIN(d), 0, COS(d)};
	double arr_v[3];
	arr_v[0] = v->x;
	arr_v[1] = v->y;
	arr_v[2] = v->z;

	double result[3];
	result[0] = 0;
	result[1] = 0;
	result[2] = 0;
	enum vv{x, y, z};
//	t_vec3 *vr = ft_create_vec3(0,0,0);
	int i = 0;
	int j = 0;
	while (i < 9)
	{
			result[j % 3] += arr_v[i % 3] * matrix_y[i];
			if (i % 3 == 2)
				j++;
		i++;
	}

	t_vec3 *vr = ft_create_vec3(result[0],result[1],result[2]);
	return (vr);
}


