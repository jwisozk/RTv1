/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 20:31:01 by jwisozk          #+#    #+#             */
/*   Updated: 2019/09/29 20:54:43 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_obj				*ft_create_object(void *obj, t_type_obj type)
{
	t_obj			*o;

	if (!(o = (t_obj*)ft_malloc(sizeof(t_obj))))
		ft_print_error(ERROR_29);
	o->type = type;
	o->objects = obj;
	o->obj = NULL;
	o->t = INF;
	o->next = NULL;
	return (o);
}

t_sphere			*ft_create_sphere(t_data *data)
{
	t_sphere		*s;

	if (!(s = (t_sphere*)ft_malloc(sizeof(t_sphere))))
		ft_print_error(ERROR_29);
	s->center = NULL;
	s->color = -1;
	s->radius = -1;
	s->specular = 0;
	s->translation = NULL;
	s->next = data->sphere != NULL ? data->sphere : NULL;
	return (s);
}

t_cylinder			*ft_create_cylinder(t_data *data)
{
	t_cylinder		*c;

	if (!(c = (t_cylinder*)ft_malloc(sizeof(t_cylinder))))
		ft_print_error(ERROR_29);
	c->center = NULL;
	c->normal = NULL;
	c->color = -1;
	c->radius = -1;
	c->specular = 0;
	c->translation = NULL;
	c->rotation = NULL;
	c->next = data->cylinder != NULL ? data->cylinder : NULL;
	return (c);
}

t_cone				*ft_create_cone(t_data *data)
{
	t_cone			*c;

	if (!(c = (t_cone*)ft_malloc(sizeof(t_cone))))
		ft_print_error(ERROR_29);
	c->center = NULL;
	c->normal = NULL;
	c->color = -1;
	c->angle = -1;
	c->specular = 0;
	c->translation = NULL;
	c->rotation = NULL;
	c->next = data->cone != NULL ? data->cone : NULL;
	return (c);
}

t_plane				*ft_create_plane(t_data *data)
{
	t_plane			*p;

	if (!(p = (t_plane*)ft_malloc(sizeof(t_plane))))
		ft_print_error(ERROR_29);
	p->normal = NULL;
	p->point = NULL;
	p->color = -1;
	p->specular = 0;
	p->translation = NULL;
	p->rotation = NULL;
	p->next = data->plane != NULL ? data->plane : NULL;
	return (p);
}
