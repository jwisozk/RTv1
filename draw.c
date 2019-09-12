/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:23:15 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/12 23:39:13 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_vec3	*ft_display_to_view(int x, int y, t_asset *p)
{
	t_vec3 *d;

	d = ft_create_point(x * p->view_w * p->dwi, -y * p->view_h * p->dhi, ZA);
	return (d);
}

int		ft_scene_intersect(t_asset *p)
{
	double plane_dist;
	double sphere_dist;
	t_sphere 	*s;

	sphere_dist = INF;
	s = ft_sphere_intersect(p->ray);
	if (s != NULL && s->t < sphere_dist)
	{
		sphere_dist = s->t;
		p->point = ft_add(p->ray->origin, ft_multiply(s->t, p->ray->direct));
		p->radius = ft_subtract(p->point, s->center);
		p->normal = ft_multiply(1.0 / ft_lenv(p->radius), p->radius);
		p->color = s->color;
		p->specular = s->specular;
	}

	plane_dist = INF;
	t_plane *pl = ft_plane_intersect(p->ray, p->p);
	if (pl != NULL && pl->t < sphere_dist && pl->t > 5)
	{
		plane_dist = pl->t;
		p->point = ft_add(p->ray->origin, ft_multiply(pl->t, p->ray->direct));
		p->normal = pl->normal;
		p->color = pl->color;
		p->specular = pl->specular;
	}


//		if (fabs(p->ray->direct->y) > 1e-3)
//	{
////		printf("%f\n", p->ray->direct->y);
//		double d = (p->ray->origin->y - 4) / p->ray->direct->y; // the checkerboard plane has equation y = -4
//		t_vec3 *pt = ft_add(p->ray->origin, ft_multiply(d, p->ray->direct));
//		if (d < sphere_dist && pt->z > 1)
//		{
//			plane_dist = d;
//			p->point = pt;
//			p->normal = ft_create_point(0, 1, 0);
//			t_vec3 *diffuse_color = ((int)(.5 * p->point->x + 1000) + (int)(.5 * p->point->z)) & 1 ? ft_create_point(0, 255, 255) : ft_create_point(255, 255, 0);
//			p->color = (ft_rgb(diffuse_color->x, diffuse_color->y, diffuse_color->z));
//			p->specular = 500;
//		}
//	}
	if (ft_min(plane_dist, sphere_dist) < INF)
		return (1);
	return (0);
}

int ft_trace_ray(t_asset *p)
{
	t_vec3 *vec_po;

	if (ft_scene_intersect(p) == 0)
		return ft_rgb(BACKGROUND);
	vec_po = ft_multiply(-1, p->ray->direct);
	double lighting = ft_lighting(p, vec_po, p->specular);
	return (ft_multiply_color(lighting, p->color));
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
			p->ray->direct = ft_display_to_view(j - offset_x, i - offset_y, p);
			p->color = ft_trace_ray(p);
			p->img.img_arr[i * DW + j] = p->color;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img.img_ptr, 0, 0);
}

