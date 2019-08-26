/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:29:39 by jwisozk           #+#    #+#             */
/*   Updated: 2019/08/26 20:29:39 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

double ft_compute_lighting(t_point *point, t_point* normal, t_asset *p)
{
	double intensity;
	double length_n;
	t_light *l;
	t_point	*vec_l;
	double n_dot_l;

	intensity = 0.0;
	length_n = ft_length_vector(normal, normal);
	l = p->l;
	while (l != NULL)
	{
		if (ft_strequ(l->type, "ambient") == 1)
			intensity += l->intensity;
		else
		{
			if (ft_strequ(l->type, "point") == 1)
				vec_l = ft_subtract(l->position, point);
			else
				vec_l = l->position;
			n_dot_l = ft_dot(normal, vec_l);
			if (n_dot_l > 0)
				intensity += l->intensity * n_dot_l / (length_n * ft_length_vector(vec_l, vec_l));

		}
		l = l->next;
	}
	return (intensity);
}


t_point	*ft_convert_ctop(t_color *color)
{
	t_point *p;

	p = (t_point*)malloc(sizeof(t_point));
	p->x = (double)color->r;
	p->y = (double)color->g;
	p->z = (double)color->b;
	return (p);
}

t_color	*ft_convert_ptoc(t_point *point)
{
	t_color *c;

	c = (t_color*)malloc(sizeof(t_color));
	c->r = (int)point->x;
	c->g = (int)point->y;
	c->b = (int)point->z;
	return (c);
}

