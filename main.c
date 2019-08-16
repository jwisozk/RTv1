/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 13:37:06 by jwisozk           #+#    #+#             */
/*   Updated: 2019/08/16 20:35:26 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int	ft_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	return ((r << 16) | (g << 8) | b);
}
//float ft_length_vector(t_vector v)
//{
//	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
////	return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
//}
//
//t_vector ft_normalize_vector(t_vector v)
//{
//	float len;
//	float inv_len;
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
//			D = CanvasToViewport(x, y)
//			color = TraceRay(O, D, 1, inf)
//			canvas.PutPixel(x, y, color)
//		}
//}

float ft_dot(t_point *v1, t_point *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_point	*ft_create_point(float x, float y, float z)
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

t_sphere *ft_create_sphere(int color, t_point *center, float radius, char *str)
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

long double	ft_map(long double n, int len, double min, double max)
{
	return (n / (len / (max - min)) + min);
}

t_point *ft_canvas_to_viewport(int x, int y)
{
	t_point *p;

//	ft_map(x, DW, f.remin, f.remax);
//	ft_map(y, DH, f.immin, f.immax);
	p = ft_create_point((float)x * 1 / DW, (float)-y * 0.5 / DH, (float)PROJECTION_PLANE_Z);
	return (p);
}

t_point *intersect_ray_sphere(t_point *camera, t_point *direction, t_sphere *sphere)
{
	t_point *intersect;
	t_point *oc = ft_subtract(camera, sphere->center);

	float k1 = ft_dot(direction, direction);
	float k2 = 2 * ft_dot(oc, direction);
	float k3 = ft_dot(oc, oc) - sphere->radius * sphere->radius;

	float discriminant = k2 * k2 - 4 * k1 * k3;
	if (discriminant < 0)
	{
		intersect = ft_create_point(INF, INF, 0);
		return (intersect);
	}
	float t1 = (-k2 + sqrt(discriminant)) / (2 * k1);
	float t2 = (-k2 - sqrt(discriminant)) / (2 * k1);
	intersect = ft_create_point(t1, t2, 0);
	return (intersect);
}

float ft_trace_ray(t_point *camera, t_point *direction, float t_min, float t_max, t_sphere *sphere)
{
float closest_t = INF;
t_sphere *closest_sphere = NULL;
t_point *t;

while (sphere != NULL)
{
	t = intersect_ray_sphere(camera, direction, sphere);
	if (t->x > t_min && t->x < t_max && t->x < closest_t)
	{
		closest_t = t->x;
		closest_sphere = sphere;
	}
	if (t->y > t_min && t->y < t_max && t->y < closest_t)
	{
		closest_t = t->y;
		closest_sphere = sphere;
	}
//	printf("%s\n", closest_sphere->str);
	sphere = sphere->next;
}

if (closest_sphere == NULL)
{
	return ft_rgb(93, 176, 200);
}
return (closest_sphere->color);
}

void	ft_draw(t_asset *p)
{
	int 	i;
	int		j;
	t_point *camera;
	t_sphere *s;
	t_point	*direction;
	int color;

	camera = ft_create_point(0, 0, 0);
	s = ft_create_sphere(ft_rgb(255, 0, 0), ft_create_point(0, -.7, 6), .7, "red");
	s->next = ft_create_sphere(ft_rgb(0, 0, 255), ft_create_point(2, 0, 2.9), 1, "blue");
	s->next->next = ft_create_sphere(ft_rgb(0, 255, 0), ft_create_point(-2.7, 0, 8), 1, "green");
	i = 0;
	while (i < DH)
	{
		j = 0;
		while (j < DW)
		{
			direction = ft_canvas_to_viewport(j - DW * 0.5, i - DH * 0.5);
//			printf("(%f, %f, %f)\n", direction->x, direction->y, direction->z);
			color = ft_trace_ray(camera, direction, 1, INF, s);
			p->img.img_arr[i * DW + j] = color;
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