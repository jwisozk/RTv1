/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:23:15 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/12 23:39:13 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void ft_sphere_fill(t_obj *obj, t_asset *p)
{
    t_sphere *s;

    s = (t_sphere*)obj->obj;
    p->point = ft_add(p->ray->origin, ft_multiply(obj->t, p->ray->direct));
    p->radius = ft_subtract(p->point, s->center);
    p->normal = ft_multiply(1.0 / ft_lenv(p->radius), p->radius);
    p->color = s->color;
    p->specular = s->specular;
}

void ft_cylinder_fill(t_obj *obj, t_asset *p)
{
    t_cylinder *c;
    c = (t_cylinder*)obj->obj;
    p->point = ft_add(p->ray->origin, ft_multiply(obj->t, p->ray->direct));
    t_vec3 *oc = ft_subtract(p->ray->origin, c->center);
    double m = ft_dot(p->ray->direct, ft_multiply(obj->t, c->normal)) + ft_dot(oc, c->normal);
    t_vec3 *pc = ft_subtract(p->point, c->center);
    p->radius = ft_subtract(pc, ft_multiply(m, c->normal));
    p->normal = ft_multiply(1.0 / ft_lenv(p->radius), p->radius);
    p->color = c->color;
    p->specular = c->specular;
}

void ft_plane_fill(t_obj *obj, t_asset *p)
{
    t_plane *pl;

    pl = (t_plane*)obj->obj;
    p->point = ft_add(p->ray->origin, ft_multiply(obj->t, p->ray->direct));
    t_vec3 *po = ft_subtract(p->ray->origin, p->point);
    double angle_on = ft_dot(pl->normal, po);
    p->normal = (angle_on < 0) ? ft_multiply(-1, pl->normal) : pl->normal;
    p->color = pl->color;
    p->specular = pl->specular;
}
