/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 22:38:24 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/27 20:46:23 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static double ft_compare_t(double t1, double t2)
{
	if (t1 > 0 && t2 > 0)
		return (ft_min(t1, t2));
	else if (0 < t1 && t1 < INF )
		return (t1);
	else if (0 < t2 && t2 < INF )
		return (t2);
	else
		return (INF);
}

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
		return(ft_compare_t(t1, t2));
	}
	return (INF);
}

void ft_sphere_intersect(t_ray *ray, t_obj *o)
{
	t_sphere 	*s;
	double		t;

	s = (t_sphere*)o->objects;
	while (s != NULL)
	{
		t = ft_intersect_ray_sphere(ray, s);
		if (t < o->t && ray->t_min < t && t < ray->t_max )
		{
			o->obj = s;
			o->t = t;
		}
		s = s->next;
	}
}

double ft_intersect_ray_cylinder(t_ray *ray, t_cylinder *c)
{
	t_vec3	*oc;
	double 	discriminant;
	double	k[3];
	double t1;
	double t2;

	oc = ft_subtract(ray->origin, c->center);
	k[0] = ft_dot(ray->direct, ray->direct) - pow(ft_dot(ray->direct, c->normal), 2);
	k[1] = 2 * (ft_dot(oc, ray->direct) - ft_dot(ray->direct, c->normal) * ft_dot(oc, c->normal));
	k[2] = ft_dot(oc, oc) - pow(ft_dot(oc, c->normal), 2) - c->radius * c->radius;
	discriminant = k[1] * k[1] - 4 * k[0] * k[2];
	if (discriminant > 0)
	{
		t1 = (-k[1] + sqrt(discriminant)) / (2 * k[0]);
		t2 = (-k[1] - sqrt(discriminant)) / (2 * k[0]);
		return(ft_compare_t(t1, t2));
	}
	return (INF);
}

void ft_cylinder_intersect(t_ray *ray, t_obj *o)
{
	t_cylinder *c;
	double		t;

	c = (t_cylinder*)o->objects;
	while (c != NULL)
	{
		t = ft_intersect_ray_cylinder(ray, c);
		if (t < o->t && ray->t_min < t && t < ray->t_max )
		{
			o->obj = c;
			o->t = t;
		}
		c = c->next;
	}
}

double ft_intersect_ray_cone(t_ray *ray, t_cone *c)
{
    t_vec3	*oc;
    double 	discriminant;
    double	k[3];
    double t1;
    double t2;

    oc = ft_subtract(ray->origin, c->center);
    k[0] = ft_dot(ray->direct, ray->direct) - (1 + pow(c->angle, 2)) * pow(ft_dot(ray->direct, c->normal), 2);
    k[1] = 2 * (ft_dot(oc, ray->direct) - (1 + pow(c->angle, 2)) * ft_dot(ray->direct, c->normal) * ft_dot(oc, c->normal));
    k[2] = ft_dot(oc, oc) - (1 + pow(c->angle, 2)) * pow(ft_dot(oc, c->normal), 2);
    discriminant = k[1] * k[1] - 4 * k[0] * k[2];
    if (discriminant > 0)
    {
        t1 = (-k[1] + sqrt(discriminant)) / (2 * k[0]);
        t2 = (-k[1] - sqrt(discriminant)) / (2 * k[0]);
		return(ft_compare_t(t1, t2));
    }
    return (INF);
}

void    ft_cone_intersect(t_ray *ray, t_obj *o)
{
    t_cone *c;
    double		t;

    c = (t_cone*)o->objects;
    while (c != NULL)
    {
        t = ft_intersect_ray_cone(ray, c);
        if (t < o->t && ray->t_min < t && t < ray->t_max )
        {
            o->obj = c;
            o->t = t;
        }
        c = c->next;
    }
}

void ft_plane_intersect(t_ray *ray, t_obj *o)
{
	t_plane *p;
	double angle;
	double t;
	t_vec3 *op;

	p = (t_plane*)o->objects;
	while (p != NULL)
	{
		angle = ft_dot(p->normal, ray->direct);
		if (angle != 0)
		{
			op = ft_subtract(p->point, ray->origin);
			t = ft_dot(op, p->normal) / angle;
			if (t < o->t && ray->t_min < t && t < ray->t_max )
			{
				o->obj = p;
				o->t = t;
			}
		}
		p = p->next;
	}
}

