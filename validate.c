/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:01:12 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/29 14:14:26 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void ft_check_camera(t_data *data)
{
	t_vec3 *a;
	t_vec3 *b;
	if (data->cam == NULL)
		ft_print_error(ft_msg(ERROR_7));
	a = data->cam->look_at;
	b = data->cam->pos;
	if(a == NULL)
		ft_print_error(ft_msg(ERROR_8));
	if (b == NULL)
		ft_print_error(ft_msg(ERROR_9));
	if (a->x == b->x &&
		a->y == b->y &&
		a->z == b->z)
		ft_print_error(ft_msg(ERROR_10));
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
			ft_print_error(ft_msg(ERROR_11));
		if (l->position == NULL)
			ft_print_error(ft_msg(ERROR_12));
		if (l->intensity < 0)
			ft_print_error(ft_msg(ERROR_13));
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
			ft_print_error(ft_msg(ERROR_14));
		if (s->radius < 0)
			ft_print_error(ft_msg(ERROR_15));
		if (s->color < 0)
			ft_print_error(ft_msg(ERROR_16));
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
			ft_print_error(ft_msg(ERROR_17));
		if (c->normal == NULL)
			ft_print_error(ft_msg(ERROR_18));
		if (c->radius < 0)
			ft_print_error(ft_msg(ERROR_19));
		if (c->color < 0)
			ft_print_error(ft_msg(ERROR_20));
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
			ft_print_error(ft_msg(ERROR_21));
		if (c->normal == NULL)
			ft_print_error(ft_msg(ERROR_22));
		if (c->angle < 0)
			ft_print_error(ft_msg(ERROR_23));
		if (c->color < 0)
			ft_print_error(ft_msg(ERROR_24));
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
			ft_print_error(ft_msg(ERROR_25));
		if (p->normal == NULL)
			ft_print_error(ft_msg(ERROR_26));
		if (p->color < 0)
			ft_print_error(ft_msg(ERROR_27));
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