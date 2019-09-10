/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 13:37:06 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/10 17:05:39 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_vec3	*ft_create_point(double x, double y, double z)
{
	t_vec3 *p;

	p = (t_vec3*)malloc(sizeof(t_vec3));
	p->x = x;
	p->y = y;
	p->z = z;
	return (p);
}

t_sphere *ft_create_sphere(int color, t_vec3 *center, double radius, char *str, int specular)
{
	t_sphere *s;

	s = (t_sphere*)malloc(sizeof(t_sphere));
	s->str = str;
	s->center = center;
	s->color = color;
	s->radius = radius;
	s->specular = specular;
	s->next = NULL;
	return (s);
}

t_ray	*ft_create_ray(t_vec3 *origin, t_vec3 *direct, double t_min, double t_max)
{
    t_ray *i;

    i = (t_ray*)malloc(sizeof(t_ray));
    i->origin = origin;
    i->direct = direct;
    i->t_min = t_min;
    i->t_max = t_max;
    return (i);
}

void	ft_invert_display_sizes(t_asset *p)
{
	p->dwi = 1.0 / DW;
	p->dhi = 1.0 / DH;
}

t_light *ft_new_light(char *type, double intensity, t_vec3 *position, int n)
{
	t_light *l;

	l = (t_light*)malloc(sizeof(t_light));
	l->type = type;
	l->intensity = intensity;
	l->position = position;
	l->n = n;
	l->next = NULL;
	return (l);
}

void	ft_init_shapes(t_asset *p)
{
	t_vec3 *camera;
	t_sphere *s1;
	t_sphere *s2;
	t_sphere *s3;
//    t_sphere *s4;

	t_light	*l1;
	t_light	*l2;
	t_light	*l3;
	t_light	*l4;

	camera = ft_create_point(0, 0, 0);
	s1 = ft_create_sphere(ft_rgb(255, 0, 0), ft_create_point(-3,    0,   16), 2, "red", 500);
	s2 = ft_create_sphere(ft_rgb(0, 0, 255), ft_create_point(-1.0, -1.5, 12), 2, "green", 500);
	s3 = ft_create_sphere(ft_rgb(0, 255, 0), ft_create_point(1.5, -0.5, 18), 3, "blue", 10);
   // s4 = ft_create_sphere(ft_rgb(255, 255, 0), ft_create_point(0, -5001, 0), 5000, "yellow", 1000);
	s1->next = s2;
	s2->next = s3;
	//s3->next = s4;
	p->s = s1;
	ft_invert_display_sizes(p);
	p->view_w = 1;
	p->view_h = 1;
	p->ray = ft_create_ray(camera, NULL, 1, INF);
	p->ray->obj = p->s;
//	l1 = ft_new_light("ambient", 0.2, ft_create_point(0, 0, 0), 1);
//	l2 = ft_new_light("point", 0.6, ft_create_point(2, 1, 0), 2);
//	l3 = ft_new_light("directional", 0.2, ft_create_point(1, 4, 4), 3);
//	l4 = ft_new_light("point", 1.5, ft_create_point(20, -20, -20), 2);

	l1 = ft_new_light("point", 0.5, ft_create_point(-20, 20,  -20), 2);
	l2 = ft_new_light("point", 0.5, ft_create_point(30, 50, 25), 2);
	l3 = ft_new_light("point", 0.5, ft_create_point(30, 20,  -30), 2);
	l4 = ft_new_light("ambient", 0.2, ft_create_point(0, 0, 0), 1);
	l1->next = l2;
	l2->next = l3;
	l3->next = l4;
	p->l = l1;
}

void	ft_open_window()
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_asset	p;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, DW, DH, "RTv1");
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