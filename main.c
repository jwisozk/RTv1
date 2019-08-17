/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 13:37:06 by jwisozk           #+#    #+#             */
/*   Updated: 2019/08/17 15:33:46 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int	ft_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	return ((r << 16) | (g << 8) | b);
}
//double ft_length_vector(t_vector v)
//{
//	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
////	return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
//}
//
//t_vector ft_normalize_vector(t_vector v)
//{
//	double len;
//	double inv_len;
//
//	len = ft_length_vector(v);
//	if (len > 0)
//	{
//		inv_len = 1 / len;
//		v.x *= inv_len;
//		v.y *= inv_len;
//		v.z *= inv_len;
//	}
//	return (v);
//}

//O = <0, 0, 0>
//for x in [-Cw/2, Cw/2] {
//		for y in [-Ch/2, Ch/2] {
//			D = CanvasToview(x, y)
//			color = TraceRay(O, D, 1, inf)
//			canvas.PutPixel(x, y, color)
//		}
//}

double ft_dot(t_point *v1, t_point *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_point	*ft_create_point(double x, double y, double z)
{
	t_point *p;

	p = (t_point*)malloc(sizeof(t_point));
	p->x = x;
	p->y = y;
	p->z = z;
	return (p);
}

t_point *ft_subtract(t_point *v1, t_point *v2)
{
	t_point *p;
	p = ft_create_point(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
	return (p);
}

t_sphere *ft_create_sphere(int color, t_point *center, double radius, char *str)
{
	t_sphere *s;

	s = (t_sphere*)malloc(sizeof(t_sphere));
	s->str = str;
	s->center = center;
	s->color = color;
	s->radius = radius;
	s->next = NULL;
	return (s);
}

t_point *ft_canvas_to_view(int x, int y, t_asset *p)
{
	t_point *d;

	d = ft_create_point(x * p->view_w * p->dwi, -y * p->view_h * p->dhi, (double)Z);
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

double ft_trace_ray(t_asset *p)
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
	if (closest_sphere != NULL)
		return (closest_sphere->color);
	return ft_rgb(BACKGROUND);
}

void	ft_invert_display_sizes(t_asset *p)
{
	p->dwi = (double)1 / DW;
	p->dhi = (double)1 / DH;
}
void	ft_init_shapes(t_asset *p)
{
	t_point *camera;
	t_sphere *s1;
	t_sphere *s2;
	t_sphere *s3;

	camera = ft_create_point(0, 0, 0);
	p->camera = camera;
	s1 = ft_create_sphere(ft_rgb(255, 0, 0), ft_create_point(-0.5, 0, 6), 1, "red");
	s2 = ft_create_sphere(ft_rgb(0, 255, 0), ft_create_point(-2.7, 0, 8), 1, "green");
	s3 = ft_create_sphere(ft_rgb(0, 0, 255), ft_create_point(0.5, 0, 7), 1, "blue");
	s1->next = s2;
	s2->next = s3;
	p->s = s1;
	ft_invert_display_sizes(p);
	p->view_w = 1;
	p->view_h = p->view_w * p->dwi * DH;
	p->t_min = 1;
	p->t_max = INF;
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
			p->direction = ft_canvas_to_view(j - offset_x, i - offset_y, p);
			p->color = ft_trace_ray(p);
			p->img.img_arr[i * DW + j] = p->color;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img.img_ptr, 0, 0);
}

void	ft_open_window()
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_asset	p;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, DW, DH + HEADER, "RTv1");
	p.img.img_ptr = mlx_new_image(mlx_ptr, DW, DH);
	p.img.img_arr = (int*)mlx_get_data_addr(p.img.img_ptr,
			&p.img.bit_per_pixel, &p.img.size_line, &p.img.endian);
	p.mlx_ptr = mlx_ptr;
	p.win_ptr = win_ptr;
	ft_init_shapes(&p);
	ft_draw(&p);
	mlx_hook(win_ptr, 17, 0, ft_close_window, &p);
	mlx_hook(win_ptr, 2, 0, ft_key_press, &p);
//	mlx_hook(win_ptr, 4, 0, ft_mouse_press, p);
//	mlx_hook(win_ptr, 5, 0, ft_mouse_release, p);
//	mlx_hook(win_ptr, 6, 0, ft_mouse_move, p);
	mlx_loop(mlx_ptr);
}
int main()
{
	ft_open_window();
	return (0);
}