/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:01:12 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/28 23:59:22 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void ft_check_camera(t_data *data)
{
	t_vec3 *a;
	t_vec3 *b;
	if (data->cam == NULL)
		ft_print_error("Error: file does not contain a camera");
	a = data->cam->look_at;
	b = data->cam->pos;
	if(a == NULL)
		ft_print_error("Error: file does not contain parameter of camera: \"look_at\"");
	if (b == NULL)
		ft_print_error("Error: file does not contain parameter of camera: \"position\"");
	if (a->x == b->x &&
		a->y == b->y &&
		a->z == b->z)
		ft_print_error("Error: parameters of camera: \"position\" and \"look_at\" equal. Impossible to determine camera direction.");
}

void ft_check_light(t_data *data)
{
	t_light *l;
	static char *arr[3] = LIGHT_TYPES;
	int i;
	int c;

	l = data->l;
	while (l != NULL)
	{
		i = 0;
		c = 0;
		while (i < 3)
		{
			if (ft_strequ(l->type, arr[i]) != 1)
				c++;
			i++;
		}
		if (c == 3)
			ft_print_error("Error: param \"type\" of light is invalid");
		if (l->position == NULL)
			ft_print_error("Error: param \"position\" of light is invalid");
		if (l->intensity < 0)
			ft_print_error("Error: param \"intensity\" of light is invalid");
		l = l->next;
	}

}

void ft_check_sphere(t_data *data)
{
	t_sphere *s;

	s = data->sphere;
	while (s != NULL)
	{
		if (s->center == NULL)
			ft_print_error("Error: param \"center\" of sphere is invalid");
		if (s->radius < 0)
			ft_print_error("Error: param \"radius\" of sphere is invalid");
		if (s->color < 0)
			ft_print_error("Error: param \"color\" of sphere is invalid");
		s = s->next;
	}
}

void ft_check_cylinder(t_data *data)
{
	t_cylinder *c;

	c = data->cylinder;
	while (c != NULL)
	{
		if (c->center == NULL)
			ft_print_error("Error: param \"center\" of cylinder is invalid");
		if (c->normal == NULL)
			ft_print_error("Error: param \"normal\" of cylinder is invalid");
		if (c->radius < 0)
			ft_print_error("Error: param \"radius\" of cylinder is invalid");
		if (c->color < 0)
			ft_print_error("Error: param \"color\" of cylinder is invalid");
		c = c->next;
	}
}

void ft_check_cone(t_data *data)
{
	t_cone *c;

	c = data->cone;
	while (c != NULL)
	{
		if (c->center == NULL)
			ft_print_error("Error: param \"center\" of cone is invalid");
		if (c->normal == NULL)
			ft_print_error("Error: param \"normal\" of cone is invalid");
		if (c->angle < 0)
			ft_print_error("Error: param \"angle\" of cone is invalid");
		if (c->color < 0)
			ft_print_error("Error: param \"color\" of cone is invalid");
		c = c->next;
	}
}

void ft_check_plane(t_data *data)
{
	t_plane *p;

	p = data->plane;
	while (p != NULL)
	{
		if (p->point == NULL)
			ft_print_error("Error: param \"point\" of plane is invalid");
		if (p->normal == NULL)
			ft_print_error("Error: param \"normal\" of plane is invalid");
		if (p->color < 0)
			ft_print_error("Error: param \"color\" of plane is invalid");
		p = p->next;
	}
}

void ft_check_valid(t_data *data)
{
	ft_check_camera(data);
	ft_check_light(data);
	ft_check_sphere(data);
	ft_check_cylinder(data);
	ft_check_cone(data);
	ft_check_plane(data);
}