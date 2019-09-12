/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 22:38:24 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/12 23:01:13 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

double ft_intersect_ray_sphere(t_ray *ray, t_sphere *s)
{
	t_vec3	*oc;
	double 	discriminant;
	double	k[3];
	double t1;
	double t2;

	oc = ft_subtract(ray->origin, s->center);
	k[0] = ft_dot(ray->direct, ray->direct);
	k[1] = 2 * ft_dot(oc, ray->direct);
	k[2] = ft_dot(oc, oc) - s->radius * s->radius;
	discriminant = k[1] * k[1] - 4 * k[0] * k[2];
	if (discriminant > 0)
	{
		t1 = (-k[1] + sqrt(discriminant)) / (2 * k[0]);
		t2 = (-k[1] - sqrt(discriminant)) / (2 * k[0]);
		return (ft_min(t1, t2));
	}
	return (INF);
}

t_sphere *ft_sphere_intersect(t_ray *ray)
{
	t_sphere 	*s;
	t_sphere 	*closest_s;
	double		closest_t;
	double		t;

	s = (t_sphere*)ray->obj;
	closest_t = INF;
	closest_s = NULL;
	while (s != NULL)
	{
		t = ft_intersect_ray_sphere(ray, s);
		if (t < closest_t && ray->t_min < t && t < ray->t_max )
		{
			closest_s = s;
			closest_s->t = t;
			closest_t = t;
		}
		s = s->next;
	}
	return (closest_s == NULL) ? NULL : closest_s;
}

t_plane *ft_plane_intersect(t_ray *ray, t_plane *pl)
{
	t_plane	*p;
	t_plane	*closest_p;
	double	closest_t;

	closest_p = NULL;
	closest_t = INF;
	p = pl;
	while (p != NULL)
	{
		double angle = ft_dot(p->normal, ray->direct);
		if (angle != 0)
		{
			t_vec3 *op = ft_subtract(p->point, ray->origin);
			double t = ft_dot(op, p->normal) / angle;
			if (t < closest_t && t > 1e-6 && ray->t_min < t && t < ray->t_max )
			{
				closest_p = p;
				closest_t = t;
				closest_p->t = t;
			}
		}
		p = p->next;
	}
	return (closest_p);
}

