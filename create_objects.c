/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iplastun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 20:31:01 by iplastun          #+#    #+#             */
/*   Updated: 2019/09/24 20:31:01 by iplastun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_obj *ft_create_object(void *obj, t_type_obj type)
{
    t_obj *o;

    o = (t_obj*)malloc(sizeof(t_obj));
    o->type = type;
    o->objects = obj;
    o->obj = NULL;
    o->t = INF;
    o->next = NULL;
    return (o);
}

t_sphere *ft_create_sphere(int color, t_vec3 *center, double radius, int specular)
{
    t_sphere *s;

    s = (t_sphere*)malloc(sizeof(t_sphere));
    s->center = center;
    s->color = color;
    s->radius = radius;
    s->specular = specular;
    s->next = NULL;
    return (s);
}

t_cylinder *ft_create_cylinder(int color, t_vec3 *center, t_vec3 *normal, double radius, int specular)
{
    t_cylinder *c;

    c = (t_cylinder*)malloc(sizeof(t_cylinder));
    c->center = center;
    c->normal = normal;
    c->color = color;
    c->radius = radius;
    c->specular = specular;
    c->next = NULL;
    return (c);
}

t_cone *ft_create_cone(int color, t_vec3 *center, t_vec3 *normal, int degree, int specular)
{
    t_cone *c;

    c = (t_cone*)malloc(sizeof(t_cone));
    c->center = center;
    c->normal = normal;
    c->color = color;
    c->angle = TANH(degree);
    c->specular = specular;
    c->next = NULL;
    return (c);
}

t_plane *ft_create_plane(int color, t_vec3 *point, t_vec3* normal, int specular)
{
    t_plane *p;

    p = (t_plane*)malloc(sizeof(t_plane));
    p->color = color;
    p->normal = normal;
    p->point = point;
    p->specular = specular;
    p->next = NULL;
    return (p);
}

