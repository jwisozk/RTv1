/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:29:39 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/13 00:19:53 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

double ft_lighting(t_asset *p, t_vec3 *vec_po, int specular)
{
	double intensity;
	t_light *l;
	t_vec3	*vec_pl;
	t_vec3 	*vec_pr;
	double angle_ln;
	double angle_rv;
	t_sphere *shadow_s;
	double t_max;
	t_ray	*ray;

	intensity = 0;
	l = p->l;
	while (l != NULL)
	{
		if (l->n == 1)
			intensity += l->intensity;
		else
		{
			if (l->n == 2)
            {
				vec_pl = ft_subtract(l->position, p->point);
			    t_max = 1.0;
            }
			else
            {
				vec_pl = l->position;
                t_max = INF;
            }

            ray = ft_create_ray(p->point, vec_pl, E, t_max);
			t_obj *new_obj1 = ft_create_object(p->o->objects, -1);
//			t_obj *new_obj1 = p->o;
//			new_obj1->obj = NULL;
//			new_obj1->t = INF;
			ft_sphere_intersect(ray, new_obj1);
			shadow_s = new_obj1->obj;

			t_obj *new_obj2 = ft_create_object(p->o->next->objects, -1);
//			t_obj *new_obj2 = p->o->next;
//			new_obj2->obj = NULL;
//			new_obj2->t = INF;
			ft_cylinder_intersect(ray, new_obj2);
			t_cylinder *shadow_c = new_obj2->obj;

			t_obj *new_obj3 = ft_create_object(p->o->next->next->objects, -1);
//			t_obj *new_obj3	= p->o->next->next;
//			new_obj3->obj = NULL;
//			new_obj3->t = INF;
			ft_plane_intersect(ray, new_obj3);
			t_plane *shadow_p = new_obj3->obj;


            if ( shadow_s != NULL || shadow_c != NULL || shadow_p != NULL)
            {
                l = l->next;
                continue ;
            }

			angle_ln = ft_dot(p->normal, vec_pl);
			if (angle_ln > 0)
				intensity += l->intensity * angle_ln / (ft_lenv(p->normal) * ft_lenv(vec_pl));

			if (specular != -1)
			{
				vec_pr = ft_subtract(ft_multiply(2.0 * ft_dot(p->normal, vec_pl), p->normal), vec_pl);
				angle_rv = ft_dot(vec_pr, vec_po) ;
				if (angle_rv > 0)
					intensity += l->intensity * pow(angle_rv / (ft_lenv(vec_pr) * ft_lenv(vec_po)), specular);
			}
		}
		l = l->next;
	}
	return (intensity);
}