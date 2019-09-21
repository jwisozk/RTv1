/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 13:37:06 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/21 21:36:40 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_vec3	*ft_create_vec3(double x, double y, double z)
{
	t_vec3 *p;

	p = (t_vec3*)malloc(sizeof(t_vec3));
	p->x = x;
	p->y = y;
	p->z = z;
	return (p);
}
t_obj *ft_create_object(void *obj, t_type_obj type)
{
	t_obj *o;

	o = (t_obj*)malloc(sizeof(t_obj));
	o->type = type;
	o->objects = obj;
	o->obj = NULL;
	o->t = INF;
	o->next = NULL;
	return (o);
}

t_sphere *ft_create_sphere(int color, t_vec3 *center, double radius, int specular)
{
	t_sphere *s;

	s = (t_sphere*)malloc(sizeof(t_sphere));
	s->center = center;
	s->color = color;
	s->radius = radius;
	s->specular = specular;
	s->next = NULL;
	return (s);
}

t_cylinder *ft_create_cylinder(int color, t_vec3 *center, t_vec3 *normal, double radius, int specular)
{
    t_cylinder *c;

    c = (t_cylinder*)malloc(sizeof(t_cylinder));
    c->center = center;
    c->normal = normal;
    c->color = color;
    c->radius = radius;
    c->specular = specular;
    c->next = NULL;
    return (c);
}

t_cone *ft_create_cone(int color, t_vec3 *center, t_vec3 *normal, int degree, int specular)
{
	t_cone *c;

	c = (t_cone*)malloc(sizeof(t_cone));
	c->center = center;
	c->normal = normal;
	c->color = color;
	c->angle = TANH(degree);
	c->specular = specular;
	c->next = NULL;
	return (c);
}

t_plane *ft_create_plane(int color, t_vec3 *point, t_vec3* normal, int specular)
{
	t_plane *p;

	p = (t_plane*)malloc(sizeof(t_plane));
	p->color = color;
	p->normal = normal;
	p->point = point;
	p->specular = specular;
	p->next = NULL;
	return (p);
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

t_point	*ft_create_point(void)
{
	t_point *p;

	p = (t_point*)malloc(sizeof(t_point));
	p->point = NULL;
	p->normal = NULL;
	p->color = ft_rgb(BACKGROUND);
	p->specular = -1;
	return (p);
}

void	ft_invert_display_sizes(t_data *data)
{
	data->dwi = 1.0 / DW;
	data->dhi = 1.0 / DH;
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

void	ft_init_shapes(t_data *data)
{
	t_obj *sphere;
	t_obj *cylinder;
	t_obj *plane;
	t_obj *cone;


	t_vec3 *camera;
	t_sphere *s1;
	t_sphere *s2;
	t_sphere *s3;
    t_sphere *s4;

	t_plane *p1;
	t_plane *p2;
	t_plane *p3;
	t_plane *p4;
	t_plane *p5;

	t_cylinder *c1;

	t_cone *co1;


	t_light	*l1;
	t_light	*l2;
	t_light	*l3;
	t_light	*l4;

	camera = ft_create_vec3(0, 0, -2);
	s1 = ft_create_sphere(ft_rgb(255, 0, 0), ft_create_vec3(0, -1.2, 3), 1, 500);
	s2 = ft_create_sphere(ft_rgb(0, 0, 255), ft_create_vec3(1, .5, 2.3), 0.5, 500);
	s3 = ft_create_sphere(ft_rgb(0, 255, 0), ft_create_vec3(-1.5, 10, 2.5), 1, 500);
    s4 = ft_create_sphere(ft_rgb(255, 255, 0), ft_create_vec3(-.6, 1.2, 3.8), 1, 500);
	s1->next = s2;
	s2->next = s3;
	s3->next = s4;

	ft_invert_display_sizes(data);
	data->view_w = 1;
	data->view_h = 1;
	data->ray = ft_create_ray(camera, NULL, 1, INF);




    p1 = ft_create_plane(ft_rgb(0, 255, 255), ft_create_vec3(12,0,0), ft_create_vec3(1,0,0), 500);
    p2 = ft_create_plane(ft_rgb(64, 128, 255), ft_create_vec3(-1,0,0), ft_create_vec3(1,0,0), 500);
    p3 = ft_create_plane(ft_rgb(255, 128, 64), ft_create_vec3(0,1,0), ft_create_vec3(0,-1,0), 500);
    p4 = ft_create_plane(ft_rgb(255, 255, 0), ft_create_vec3(0,-1,0), ft_create_vec3(0,1,0), 500);
	p5 = ft_create_plane(ft_rgb(200, 100, 64), ft_create_vec3(0,0,10), ft_create_vec3(0,0,-1), 500);
	p1->next = p2;
	p2->next = p3;
	p3->next = p4;
	p4->next = p5;


	c1 = ft_create_cylinder(ft_rgb(255, 255, 100), ft_create_vec3(1, 2, 3), ft_create_vec3(0, 1, 0), 0.3, 500);
	co1 = ft_create_cone(ft_rgb(100, 255, 100), ft_create_vec3(0, 0, 2.7), ft_create_vec3(0, 1, 0), 30, 500);


	sphere = ft_create_object(s1, SPHERE);
	cylinder = ft_create_object(c1, CYLINDER);
	plane = ft_create_object(p1, PLANE);
	cone = ft_create_object(co1, CONE);
	sphere->next = cylinder;
	cylinder->next = plane;
	plane->next = cone;
	data->o = sphere;


	l1 = ft_new_light("ambient", 0.2, ft_create_vec3(0, 0, 0), 1);
	l2 = ft_new_light("point", 0.7, ft_create_vec3(-.7, -.48, 1.8), 2);
	l3 = ft_new_light("directional", 0.0, ft_create_vec3(7, 2, 3), 3);
	l4 = ft_new_light("point", 0.5, ft_create_vec3(.9, -.7, 2.2), 2);
//	l1 = ft_new_light("point", 0.5, ft_create_vec3(-20, 20,  -20), 2);
//	l2 = ft_new_light("point", 0.5, ft_create_vec3(30, 50, 25), 2);
//	l3 = ft_new_light("point", 0.5, ft_create_vec3(30, 20,  -30), 2);
//	l4 = ft_new_light("ambient", 0.2, ft_create_vec3(0, 0, 0), 1);
	l1->next = l2;
	l2->next = l3;
	l3->next = l4;
	data->l = l1;

	data->p = ft_create_point();

}

void	ft_open_window()
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	data;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, DW, DH, "RTv1");
	data.img.img_ptr = mlx_new_image(mlx_ptr, DW, DH);
	data.img.img_arr = (int*)mlx_get_data_addr(data.img.img_ptr,
			&data.img.bit_per_pixel, &data.img.size_line, &data.img.endian);
	data.mlx_ptr = mlx_ptr;
	data.win_ptr = win_ptr;
	ft_init_shapes(&data);
	ft_draw(&data);
	mlx_hook(win_ptr, 17, 0, ft_close_window, &data);
	mlx_hook(win_ptr, 2, 0, ft_key_press, &data);
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