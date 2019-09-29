/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometric_create.c                      		    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 20:41:27 by iplastun          #+#    #+#             */
/*   Updated: 2019/09/27 16:40:33 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_vec3	*ft_create_vec3(double x, double y, double z)
{
    t_vec3 *p;

    p = (t_vec3*)malloc(sizeof(t_vec3));
    p->x = x;
    p->y = y;
    p->z = z;
    return (p);
}

t_ang3	*ft_create_ang3(int x, int y, int z)
{
    t_ang3 *a;

    a = (t_ang3*)malloc(sizeof(t_ang3));
    a->x = x;
    a->y = y;
    a->z = z;
    return (a);
}

t_ray	*ft_create_ray(t_vec3 *origin, t_vec3 *direct, double t_min, double t_max)
{
    t_ray *i;

    i = (t_ray*)malloc(sizeof(t_ray));
    i->origin = origin;
    i->direct = direct;
    i->t_min = t_min;
    i->t_max = t_max;
    return (i);
}

t_point	*ft_create_point(void)
{
    t_point *p;

    p = (t_point*)malloc(sizeof(t_point));
    p->point = NULL;
    p->normal = NULL;
    p->color = ft_rgb(BACKGROUND);
    p->specular = -1;
    p->vec_oc = NULL;
    p->radius = 0;
    return (p);
}