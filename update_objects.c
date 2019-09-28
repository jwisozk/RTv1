/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:06:14 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/28 19:09:17 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void 	ft_update_sphere(t_data *data, t_lst* lst)
{
	t_sphere 	*s;
	double		*d;
	int 		*i;

	s = ft_create_sphere(data);
	while (lst != NULL)
	{
		i = (int*)lst->data;
		d = (double*)lst->data;
		if (ft_strequ(lst->type, "center") == 1)
			s->center = ft_create_vec3(d[0], d[1], d[2]);
		else if (ft_strequ(lst->type, "translation"))
			s->translation = ft_create_vec3(d[0], d[1], d[2]);
		else if (ft_strequ(lst->type, "color") == 1)
			s->color = ft_rgb(i[0], i[1], i[2]);
		else if (ft_strequ(lst->type, "radius"))
			s->radius = ft_atof((char*)lst->data);
		else if (ft_strequ(lst->type, "specular"))
			s->specular = ft_atoi((char*)lst->data);
		lst = lst->next;
	}
	if (s->translation != NULL)
		s->center = ft_translate(s->center, s->translation);
	data->sphere = s;
}



void 		ft_update_cylinder(t_data *data, t_lst* lst)
{
	t_cylinder 	*c;
	double		*d;
	int 		*i;

	c = ft_create_cylinder(data);
	while (lst != NULL)
	{
		i = (int*)lst->data;
		if (ft_strequ(lst->type, "color") == 1)
			c->color = ft_rgb(i[0], i[1], i[2]);
		else if (ft_strequ(lst->type, "rotation"))
			c->rotation = ft_create_ang3(i[0], i[1], i[2]);
		else if (ft_strequ(lst->type, "specular") == 1)
			c->specular = ft_atoi((char*)lst->data);
		else if (ft_strequ(lst->type, "radius"))
			c->radius = ft_atof((char*)lst->data);
		else
		{
			d = (double*)lst->data;
			if (ft_strequ(lst->type, "center") == 1)
				c->center = ft_create_vec3(d[0], d[1], d[2]);
			else if (ft_strequ(lst->type, "translation"))
				c->translation = ft_create_vec3(d[0], d[1], d[2]);
			else if (ft_strequ(lst->type, "normal"))
				c->normal = ft_create_vec3(d[0], d[1], d[2]);
		}
		lst = lst->next;
	}
	if (c->translation != NULL)
		c->center = ft_translate(c->center, c->translation);
	if (c->rotation != NULL)
		c->normal = ft_rotate(c->normal, c->rotation);
	data->cylinder = c;
}


void 					ft_update_cone(t_data *data, t_lst* lst)
{
	t_cone 		*c;
	double		*d;
	int 		*i;

	c = ft_create_cone(data);
	while (lst != NULL)
	{
		i = (int*)lst->data;
		if (ft_strequ(lst->type, "color") == 1)
			c->color = ft_rgb(i[0], i[1], i[2]);
		else if (ft_strequ(lst->type, "rotation"))
			c->rotation = ft_create_ang3(i[0], i[1], i[2]);
		else if (ft_strequ(lst->type, "specular") == 1)
			c->specular = ft_atoi((char*)lst->data);
		else if (ft_strequ(lst->type, "angle"))
			c->angle = TANH(ft_atoi((char*)lst->data));
		else
		{
			d = (double*)lst->data;
			if (ft_strequ(lst->type, "center") == 1)
				c->center = ft_create_vec3(d[0], d[1], d[2]);
			else if (ft_strequ(lst->type, "translation"))
				c->translation = ft_create_vec3(d[0], d[1], d[2]);
			else if (ft_strequ(lst->type, "normal"))
				c->normal = ft_create_vec3(d[0], d[1], d[2]);
		}
		lst = lst->next;
	}
	if (c->translation != NULL)
		c->center = ft_translate(c->center, c->translation);
	if (c->rotation != NULL)
		c->normal = ft_rotate(c->normal, c->rotation);
	data->cone = c;
}


void 	ft_update_plane(t_data *data, t_lst* lst)
{
	t_plane 	*p;
	double		*d;
	int 		*i;

	p = ft_create_plane(data);
	while (lst != NULL)
	{
		i = (int*)lst->data;
		if (ft_strequ(lst->type, "color") == 1)
			p->color = ft_rgb(i[0], i[1], i[2]);
		else if (ft_strequ(lst->type, "rotation"))
			p->rotation = ft_create_ang3(i[0], i[1], i[2]);
		else if (ft_strequ(lst->type, "specular") == 1)
			p->specular = ft_atoi((char*)lst->data);
		else
		{
			d = (double*)lst->data;
			if (ft_strequ(lst->type, "point") == 1)
				p->point = ft_create_vec3(d[0], d[1], d[2]);
			else if (ft_strequ(lst->type, "translation"))
				p->translation = ft_create_vec3(d[0], d[1], d[2]);
			else if (ft_strequ(lst->type, "normal"))
				p->normal = ft_create_vec3(d[0], d[1], d[2]);
		}
		lst = lst->next;
	}
	if (p->translation != NULL)
		p->point = ft_translate(p->point, p->translation);
	if (p->rotation != NULL)
		p->normal = ft_rotate(p->normal, p->rotation);
	data->plane = p;
}