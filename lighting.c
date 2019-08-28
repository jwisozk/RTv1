/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:29:39 by jwisozk           #+#    #+#             */
/*   Updated: 2019/08/28 14:37:42 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

double ft_lighting(t_asset *p)
{
	double intensity;
	double length_n;
	t_light *l;
	t_point	*vec_l;
	double n_dot_l;

	intensity = 0.0;
	length_n = ft_lenv(p->normal);
	l = p->l;
	while (l != NULL)
	{
		if (ft_strequ(l->type, "ambient") == 1)
			intensity += l->intensity;
		else
		{
			if (ft_strequ(l->type, "point") == 1)
				vec_l = ft_subtract(l->position, p->point);
			else
				vec_l = l->position;
			n_dot_l = ft_dot(p->normal, vec_l);
			if (n_dot_l > 0)
				intensity += l->intensity * n_dot_l / (length_n * ft_lenv(vec_l));
		}
		l = l->next;
	}
	return (intensity);
}