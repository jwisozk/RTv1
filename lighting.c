/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:29:39 by jwisozk           #+#    #+#             */
/*   Updated: 2019/08/28 16:48:35 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

double ft_lighting(t_asset *p, t_point *view, t_sphere *s)
{
	double intensity;
	double length_n;
	t_light *l;
	t_point	*vec_l;
	double n_dot_l;
	double length_v;

	intensity = 0;
	length_v  = ft_lenv(view);
	length_n = ft_lenv(p->normal);
	l = p->l;
	while (l != NULL)
	{
		if (l->n == 1)
			intensity += l->intensity;
		else
		{
			if (l->n == 2)
				vec_l = ft_subtract(l->position, p->point);
			else
				vec_l = l->position;

			n_dot_l = ft_dot(p->normal, vec_l);
			if (n_dot_l > 0)
				intensity += l->intensity * n_dot_l / (length_n * ft_lenv(vec_l));

			if (s->specular != -1)
			{
				t_point *vec_r = ft_subtract(ft_multiply(2.0 * n_dot_l, p->normal), vec_l);
				double r_dot_v = ft_dot(vec_r, view);
				if (r_dot_v > 0)
					intensity += l->intensity * pow(r_dot_v / (ft_lenv(vec_r) * length_v), s->specular);
			}
		}
		l = l->next;
	}
	return (intensity);
}