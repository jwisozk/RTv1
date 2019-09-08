/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:29:39 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/08 23:43:33 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

double ft_lighting(t_asset *p, t_point *view, int specular)
{
	double intensity;
	double length_n;
	t_light *l;
	t_point	*vec_l;
	double n_dot_l;
	double length_v;
	t_sphere *shadow_s;
	double t_max;

//	t_point *a;
//	t_point *b;
//	double min;
//	double max;

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
            {
			    vec_l = ft_subtract(l->position, p->point);
			    t_max = 1.0;
            }
			else
            {
			    vec_l = l->position;
                t_max = INF;
            }
//			a = p->camera;
//			b = p->direction;
//			min = p->t_min;
//			max = p->t_max;
//			p->camera = p->point;
//			p->direction = vec_l;
//			p->t_min = E;
//			p->t_max = t_max;
//			if (scene_intersectl(p, ft_create_intersect(p->point, vec_l, E, t_max)) == 1)
//			{
//				l = l->next;
//				continue ;
//			}
//			p->camera = a;
//			p->direction = b;
//			p->t_min = min;
//			p->t_max = max;
            shadow_s = ft_closest_intersection(p, ft_create_intersect(p->point, vec_l, E, t_max));
            if (shadow_s != NULL)
            {
                l = l->next;
                continue ;
            }

			n_dot_l = ft_dot(p->normal, vec_l);
			if (n_dot_l > 0)
				intensity += l->intensity * n_dot_l / (length_n * ft_lenv(vec_l));

			if (specular != -1)
			{
				t_point *vec_r = ft_subtract(ft_multiply(2.0 * n_dot_l, p->normal), vec_l);
				double r_dot_v = ft_dot(vec_r, view);
				if (r_dot_v > 0)
					intensity += l->intensity * pow(r_dot_v / (ft_lenv(vec_r) * length_v), specular);
			}
		}
		l = l->next;
	}
	return (intensity);
}