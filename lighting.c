/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:29:39 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/30 18:43:40 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double				ft_add_diffuse_light(t_point *p, t_light *l, t_vec3 *vec_pl)
{
	double			angle_ln;

//	if (p == NULL)
//	{
	angle_ln = ft_dot(p->normal, vec_pl);
	if (p->vec_oc != NULL && ft_lenv(p->vec_oc) < p->radius)
		angle_ln *= -1;
	if (angle_ln > 0)
		{
			return (l->intensity * angle_ln /
			(ft_lenv(p->normal) * ft_lenv(vec_pl)));
		}
//	}
	return (0);
}

double				ft_add_specular_light(t_point *p, t_light *l,
					t_vec3 *vec_pl, t_vec3 *vec_po)
{
	t_vec3			*vec_pr;
	double			angle_rv;

	if (p->specular > 0)
	{
		vec_pr = ft_subtract(ft_multiply(2.0 * ft_dot(p->normal, vec_pl),
		p->normal), vec_pl);
		angle_rv = ft_dot(vec_pr, vec_po);
		if (angle_rv > 0)
			return (l->intensity * pow(angle_rv /
			(ft_lenv(vec_pr) * ft_lenv(vec_po)), p->specular));
	}
	return (0);
}

int					ft_add_shadow(t_ray *ray, t_obj *o, t_light **l)
{
	if (ft_scene_intersect(o, ray) != NULL)
	{
		(*l) = (*l)->next;
		return (1);
	}
	return (0);
}

double				ft_lighting(t_point *p, t_light *l, t_obj *o,
					t_vec3 *vec_po)
{
	double			intensity;
	t_vec3			*vec_pl;
	double			t_max;
	t_ray			*ray;

	intensity = 0;
	while (l != NULL)
	{
		if (ft_strequ(l->type, AMBIENT) == 1)
			intensity += l->intensity;
		else if (ft_strequ(l->type, POINT) == 1 ||
		ft_strequ(l->type, DIRECTIONAL) == 1)
		{
			vec_pl = (ft_strequ(l->type, POINT) == 1) ?
			ft_subtract(l->position, p->point) : l->position;
			t_max = (ft_strequ(l->type, POINT) == 1) ? 1.0 : INF;
			ray = ft_create_ray(p->point, vec_pl, E, t_max);
			if (ft_add_shadow(ray, o, &l) == 1)
				continue ;
			intensity += ft_add_diffuse_light(p, l, vec_pl);
			intensity += ft_add_specular_light(p, l, vec_pl, vec_po);
		}
		l = l->next;
	}
	return (intensity);
}
