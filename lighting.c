/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:29:39 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/10 18:36:38 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

double ft_lighting(t_asset *p, t_vec3 *view, int specular)
{
	double intensity;
	t_light *l;
	t_vec3	*pl;
	double angle_ln;
	double length_v;
	t_sphere *shadow_s;
	double t_max;
	t_ray	*ray;

	intensity = 0;
	length_v  = ft_lenv(view);
	l = p->l;
	while (l != NULL)
	{
		if (l->n == 1)
			intensity += l->intensity;
		else
		{
			if (l->n == 2)
            {
				pl = ft_subtract(l->position, p->point);
			    t_max = 1.0;
            }
			else
            {
				pl = l->position;
                t_max = INF;
            }
			ray = ft_create_ray(p->point, pl, E, t_max);
			ray->obj = (void*)p->s;
			shadow_s = ft_sphere_intersect(ray);
            if (shadow_s != NULL)
            {
                l = l->next;
                continue ;
            }

			angle_ln = ft_dot(p->normal, pl) / (ft_lenv(p->normal) * ft_lenv(pl));
			if (angle_ln > 0)
				intensity += l->intensity * angle_ln;

			specular = 500;
			if (specular != -1)
			{
				t_vec3 *vec_r = ft_subtract(ft_multiply(2.0 * angle_ln, p->normal), pl);
				double r_dot_v = ft_dot(vec_r, view);
				if (r_dot_v > 0)
					intensity += l->intensity * pow(r_dot_v / (ft_lenv(vec_r) * length_v), specular);
			}
		}
		l = l->next;
	}
	return (intensity);
}