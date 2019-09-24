/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iplastun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 13:37:06 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/24 20:52:22 by iplastun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	ft_init_shapes(t_data *data)
{
	t_obj *sphere;
//	t_obj *cylinder;
	t_obj *plane;
//	t_obj *cone;


	t_vec3 *camera;
	t_sphere *s1;
//	t_sphere *s2;
//	t_sphere *s3;
//    t_sphere *s4;

	t_plane *p1;
	t_plane *p2;
	t_plane *p3;
	t_plane *p4;
	t_plane *p5;

//	t_cylinder *c1;
//
//	t_cone *co1;


	t_light	*l1;
	t_light	*l2;
	t_light	*l3;
//	t_light	*l4;

    t_ang3 *a;
	t_vec3 *t;

//    a = ft_create_ang3(30,90,30);
//    t = ft_create_vec3(2,1,2);
//	a = ft_create_ang3(30,90,0);
//	t = ft_create_vec3(2,0,2);
	a = ft_create_ang3(0,0,0);
	t = ft_create_vec3(0.3,0.0,0.05);
	camera = ft_create_vec3(0, 0, 0);
	s1 = ft_create_sphere(ft_rgb(255, 0, 0), ft_create_vec3(0, 0, 0), 0.5, 500);
//	s2 = ft_create_sphere(ft_rgb(0, 0, 255), ft_create_vec3(1, .5, 2.3), 0.5, 500);
//	s3 = ft_create_sphere(ft_rgb(0, 255, 0), ft_create_vec3(-1.5, 10, 2.5), 1, 500);
//    s4 = ft_create_sphere(ft_rgb(255, 255, 0), ft_create_vec3(-.6, 1.2, 3.8), 1, 500);
//	s1->next = s2;
//	s2->next = s3;
//	s3->next = s4;

//	ft_invert_display_sizes(data);
//	data->view_w = 1;
//	data->view_h = 1;


	data->ray = ft_create_ray(camera, NULL, 1, INF);
    data->ray->a = a;
	data->ray->t = t;



    p1 = ft_create_plane(ft_rgb(0, 255, 255), ft_create_vec3(3,0,0), ft_create_vec3(1,0,0), 500);
    p2 = ft_create_plane(ft_rgb(64, 128, 255), ft_create_vec3(-3,0,0), ft_create_vec3(1,0,0), 500);
    p3 = ft_create_plane(ft_rgb(255, 128, 64), ft_create_vec3(0,-3,0), ft_create_vec3(0,-1,0), 500);
    p4 = ft_create_plane(ft_rgb(255, 255, 0), ft_create_vec3(0,0,-3), ft_create_vec3(0,0,1), 500);
	p5 = ft_create_plane(ft_rgb(230, 220, 64), ft_create_vec3(0,0,3), ft_create_vec3(0,0,-1), 500);
	p1->next = p2;
	p2->next = p3;
	p3->next = p4;
	p4->next = p5;


//	c1 = ft_create_cylinder(ft_rgb(255, 255, 100), ft_create_vec3(1, 2, 3), ft_create_vec3(0, 1, 0), 0.3, 500);
//	co1 = ft_create_cone(ft_rgb(100, 255, 100), ft_create_vec3(0, 0, 2.7), ft_create_vec3(0, 1, 0), 30, 500);


	sphere = ft_create_object(s1, SPHERE);
//	cylinder = ft_create_object(c1, CYLINDER);
	plane = ft_create_object(p1, PLANE);
//	cone = ft_create_object(co1, CONE);
	sphere->next = plane;
//	plane->next = cylinder;
//    cylinder->next = cone;
	data->o = sphere;


	l1 = ft_new_light("ambient", 0.2, ft_create_vec3(0, 0, 0), 1);
	l2 = ft_new_light("point", 0.7, ft_create_vec3(1, 0, 0), 2);
	l3 = ft_new_light("directional", 0.0, ft_create_vec3(1, 0, 0), 3);
//	l4 = ft_new_light("point", 0.5, ft_create_vec3(.9, -.7, 2.2), 2);
//	l1 = ft_new_light("point", 0.5, ft_create_vec3(-20, 20,  -20), 2);
//	l2 = ft_new_light("point", 0.5, ft_create_vec3(30, 50, 25), 2);
//	l3 = ft_new_light("point", 0.5, ft_create_vec3(30, 20,  -30), 2);
//	l4 = ft_new_light("ambient", 0.2, ft_create_vec3(0, 0, 0), 1);
	l1->next = l2;
	l2->next = l3;
//	l3->next = l4;
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
	return (0);
}