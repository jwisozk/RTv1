/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:23:15 by jwisozk           #+#    #+#             */
/*   Updated: 2019/08/29 14:11:19 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_point *ft_display_to_view(int x, int y, t_asset *p)
{
	t_point *d;

	d = ft_create_point(x * p->view_w * p->dwi, -y * p->view_h * p->dhi, ZA);
	return (d);
}

t_point *intersect_ray_sphere(t_asset *p, t_sphere *sphere)
{
	t_point *cam_to_sc;
	t_point *intersect;
	double 	discriminant;

	double 	k1;
	double 	k2;
	double 	k3;

	double t1;
	double t2;

	cam_to_sc = ft_subtract(p->camera, sphere->center);
	k1 = ft_dot(p->direction, p->direction);
	k2 = 2 * ft_dot(cam_to_sc, p->direction);
	k3 = ft_dot(cam_to_sc, cam_to_sc) - sphere->radius * sphere->radius;
	discriminant = k2 * k2 - 4 * k1 * k3;
	if (discriminant > 0)
	{
		t1 = (-k2 + sqrt(discriminant)) / (2 * k1);
		t2 = (-k2 - sqrt(discriminant)) / (2 * k1);
		intersect = ft_create_point(t1, t2, 0);
	}
	else
		intersect = ft_create_point(INF, INF, 0);
	return (intersect);
}

int ft_trace_ray(t_asset *p)
{
	t_sphere 	*closest_s;
	t_sphere 	*s;
	t_point		*t;
	double		closest_t;

	closest_t = INF;
	closest_s = NULL;
	s = p->s;
	while (s != NULL)
	{
		t = intersect_ray_sphere(p, s);
		if (t->x < closest_t && p->t_min < t->x && t->x < p->t_max )
		{
			closest_t = t->x;
			closest_s = s;
		}

		if (t->y < closest_t && p->t_min < t->y && t->y < p->t_max)
		{
			closest_t = t->y;
			closest_s = s;
		}
		free(t);
		s = s->next;
	}
	if (closest_s == NULL)
		return ft_rgb(93, 176, 200);

	p->point = ft_add(p->camera, ft_multiply(closest_t, p->direction));
	p->radius = ft_subtract(p->point, closest_s->center);
	p->normal = ft_multiply(1.0 / ft_lenv(p->radius), p->radius);

	t_point *view = ft_multiply(-1, p->direction);
	double lighting = ft_lighting(p, view, closest_s);
	return (ft_multiply_color(lighting, closest_s->color));
}

void	ft_draw(t_asset *p)
{
	int 	i;
	int		j;
	int 	offset_x;
    int     offset_y;

	offset_x = (int)(DW * 0.5);
	offset_y = (int)(DH * 0.5);
	i = 0;
	while (i < DH)
	{
		j = 0;
		while (j < DW)
		{
			p->direction = ft_display_to_view(j - offset_x, i - offset_y, p);
			p->color = ft_trace_ray(p);
			p->img.img_arr[i * DW + j] = p->color;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img.img_ptr, 0, 0);
}

