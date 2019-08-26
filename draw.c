/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:23:15 by jwisozk           #+#    #+#             */
/*   Updated: 2019/08/26 21:02:27 by jwisozk          ###   ########.fr       */
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

t_color *ft_trace_ray(t_asset *p)
{
	t_sphere 	*closest_sphere;
	t_sphere 	*sphere;
	t_point		*t;
	double		closest_t;

	closest_t = INF;
	closest_sphere = NULL;
	sphere = p->s;
	while (sphere != NULL)
	{
		t = intersect_ray_sphere(p, sphere);
		if (t->x > p->t_min && t->x < p->t_max && t->x < closest_t)
		{
			closest_t = t->x;
			closest_sphere = sphere;
		}

		if (t->y > p->t_min && t->y < p->t_max && t->y < closest_t)
		{
			closest_t = t->y;
			closest_sphere = sphere;
		}
		free(t);
		sphere = sphere->next;
	}
	if (closest_sphere == NULL)
		return ft_rgb_rev(93, 176, 200);

	t_point *point = ft_add(p->camera, ft_multiply(closest_t, p->direction));
	t_point *normal = ft_subtract(point, closest_sphere->center);
	normal = ft_multiply(1.0 / ft_length_vector(normal, normal), normal);

	t_point *m = ft_multiply(ft_compute_lighting(point, normal, p), ft_convert_ctop(closest_sphere->color));
	return (ft_convert_ptoc(m));
}

void	ft_draw(t_asset *p)
{
	int 	i;
	int		j;
	int 	offset_x;
	int 	offset_y;

	offset_x = DW * 0.5;
	offset_y = DH * 0.5;
	i = 0;
	while (i < DH)
	{
		j = 0;
		while (j < DW)
		{
			p->direction = ft_display_to_view(j - offset_x, i - offset_y, p);
			p->color = ft_trace_ray(p);
			p->img.img_arr[i * DW + j] = ft_clamp(p->color);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img.img_ptr, 0, 0);
}

