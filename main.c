/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 13:37:06 by jwisozk           #+#    #+#             */
/*   Updated: 2019/08/24 22:13:27 by jwisozk          ###   ########.fr       */
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

double ft_length_vector(t_point *v1, t_point *v2)
{
	return sqrt(ft_dot(v1, v2));
}

t_point *ft_multiply(double k, t_point *v)
{
	v->x *= k;
	v->y *= k;
	v->z *= k;
	return (v);
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

t_point *ft_add(t_point *v1, t_point *v2)
{
	t_point *p;
	p = ft_create_point(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z);
	return (p);
}

int ft_clamp(t_color *v)
{
	return(ft_rgb(min(255, max(0, v->r)), min(255, max(0, v->g)), min(255, max(0, v->b))));
}

t_sphere *ft_create_sphere(t_color *color, t_point *center, double radius, char *str)
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
//
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
		t1 = (-k2 + sqrtf(discriminant)) / (2 * k1);
		t2 = (-k2 - sqrtf(discriminant)) / (2 * k1);
		intersect = ft_create_point(t1, t2, 0);
	}
	else
		intersect = ft_create_point(INF, INF, 0);
	return (intersect);
}

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
t_color *ft_rgb_rev(int r, int g, int b)
{
	t_color *c;

	c = (t_color*)malloc(sizeof(t_color));
	c->r = r;
	c->g = g;
	c->b = b;
	return (c);
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

void	ft_invert_display_sizes(t_asset *p)
{
	p->dwi = (double)1 / DW;
	p->dhi = (double)1 / DH;
}

t_light *ft_new_light(char *type, double intensity, t_point *position)
{
	t_light *l;

	l = (t_light*)malloc(sizeof(t_light));
	l->type = type;
	l->intensity = intensity;
	l->position = position;
	l->next = NULL;
	return (l);
}

void	ft_init_shapes(t_asset *p)
{
	t_point *camera;
	t_sphere *s1;
	t_sphere *s2;
	t_sphere *s3;

	t_light	*l1;
	t_light	*l2;
	t_light	*l3;
	t_light	*l4;

	camera = ft_create_point(0, 0, 0);
	p->camera = camera;
	s1 = ft_create_sphere(ft_rgb_rev(69, 28, 26), ft_create_point(0, 0, 6), 1, "red");
	s2 = ft_create_sphere(ft_rgb_rev(102, 102, 79), ft_create_point(-2, 0, 7), 1, "green");
	s3 = ft_create_sphere(ft_rgb_rev(102, 102, 79), ft_create_point(2, 0, 8), 1, "blue");
	s1->next = s2;
	s2->next = s3;
	p->s = s1;
	ft_invert_display_sizes(p);
	p->view_w = 1;
	p->view_h = p->view_w * p->dwi * DH;
	p->t_min = 1;
	p->t_max = INF;


	l1 = ft_new_light("ambient", 0.2, ft_create_point(0, 0, 0));
	l2 = ft_new_light("point", 1.5, ft_create_point(-20, 20, -20));
	l3 = ft_new_light("directional", 0.5, ft_create_point(-20, 20, -20));
	l4 = ft_new_light("point", 1.5, ft_create_point(20, -20, -20));
	l1->next = l2;
	l2->next = l3;
	l3->next = l4;
	p->l = l1;
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
//			if (p->color->r != 255)
//				printf("r = %i, g = %i, b = %i", p->color->r, p->color->g, p->color->b);
//			printf("%i\n",ft_clamp(p->color));
			p->img.img_arr[i * DW + j] = ft_clamp(p->color);
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
//	primary_ray();
	return (0);
}