/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:23:15 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/08 23:54:13 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_point *ft_display_to_view(int x, int y, t_asset *p)
{
	t_point *d;

	d = ft_create_point(x * p->view_w * p->dwi, -y * p->view_h * p->dhi, ZA);
	return (d);
}

t_point *intersect_ray_sphere(t_intersect *i, t_sphere *sphere)
{
	t_point *cam_to_sc;
	t_point *intersect;
	double 	discriminant;

	double 	k1;
	double 	k2;
	double 	k3;

	double t1;
	double t2;

	cam_to_sc = ft_subtract(i->origin, sphere->center);
	k1 = ft_dot(i->direct, i->direct);
	k2 = 2 * ft_dot(cam_to_sc, i->direct);
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

t_sphere *ft_closest_intersection(t_asset *p, t_intersect *i)
{
    double		closest_t;
    t_sphere 	*closest_s;
    t_sphere 	*s;
    t_point		*t;

    s = p->s;
    closest_t = INF;
    closest_s = NULL;
    while (s != NULL)
    {
        t = intersect_ray_sphere(i, s);
        if (t->x < closest_t && i->t_min < t->x && t->x < i->t_max )
        {
            closest_t = t->x;
            closest_s = s;
			closest_s->closest_t = t->x;
        }

        if (t->y < closest_t && i->t_min < t->y && t->y < i->t_max)
        {
            closest_t = t->y;
            closest_s = s;
			closest_s->closest_t = t->y;
        }
//        printf("%f\n", closest_s->closest_t);
        free(t);
        s = s->next;
    }
//    printf("HERE\n");
	return (closest_s == NULL) ? NULL : closest_s;
//    return (closest_s);
}

int scene_intersect(t_asset *p)
{
	double plane_dist;
	double sphere_dist;
	t_sphere 	*s;


	sphere_dist = INF;
	s = ft_closest_intersection(p, ft_create_intersect(p->camera, p->direction, p->t_min, p->t_max));

	if (s != NULL && s->closest_t < sphere_dist)
	{
		sphere_dist = s->closest_t;
		p->point = ft_add(p->camera, ft_multiply(s->closest_t, p->direction));
		p->radius = ft_subtract(p->point, s->center);
		p->normal = ft_multiply(1.0 / ft_lenv(p->radius), p->radius);
		p->color = s->color;
		p->specular = s->specular;
	}

	plane_dist = INF;
	if (fabs(p->direction->y) > 1e-3)
	{
		double d = -(p->camera->y+4) / p->direction->y; // the checkerboard plane has equation y = -4
		t_point *pt = ft_add(p->camera, ft_multiply(d, p->direction));
		if (d < sphere_dist && fabs(pt->x) < 10 && pt->z > 10 && pt->z < 30)
		{
			plane_dist = d;
			p->point = pt;
			p->normal = ft_create_point(0,1,0);
			t_point *diffuse_color = ((int)(.5 * p->point->x + 1000) + (int)(.5 * p->point->z)) & 1 ? ft_create_point(0, 255, 255) : ft_create_point(255, 255, 0);
			p->color = (ft_rgb(diffuse_color->x, diffuse_color->y, diffuse_color->z));
			p->specular = 500;
		}
	}

	if (ft_min(plane_dist, sphere_dist) < INF)
		return (1);
	return (0);
}

int ft_trace_ray(t_asset *p)
{


	// s = ft_closest_intersection(p, ft_create_intersect(p->camera, p->direction, p->t_min, p->t_max));
	if (scene_intersect(p) == 0)
		return ft_rgb(BACKGROUND);
//    if (s == NULL)
//		return ft_rgb(BACKGROUND);
//	p->point = ft_add(p->camera, ft_multiply(s->closest_t, p->direction));
//	p->radius = ft_subtract(p->point, s->center);
//	p->normal = ft_multiply(1.0 / ft_lenv(p->radius), p->radius);

	t_point *view = ft_multiply(-1, p->direction);
	double lighting = ft_lighting(p, view, p->specular);
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
			p->direction = ft_display_to_view(j - offset_x, i - offset_y, p);
			p->color = ft_trace_ray(p);
			p->img.img_arr[i * DW + j] = p->color;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img.img_ptr, 0, 0);
}

