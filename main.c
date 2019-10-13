/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iplastun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 17:05:58 by jwisozk           #+#    #+#             */
/*   Updated: 2019/10/13 14:32:43 by iplastun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				ft_init_shapes(t_data *data)
{
	data->sphere = NULL;
	data->plane = NULL;
	data->cylinder = NULL;
	data->cone = NULL;
	data->p = ft_create_point();
	data->o = NULL;
	data->l = NULL;
	data->cam = NULL;
	data->pass = NULL;
}

void				ft_check_valid(t_data *data)
{
	ft_check_camera(data);
	ft_check_light(data);
	ft_check_sphere(data);
	ft_check_cylinder(data);
	ft_check_cone(data);
	ft_check_plane(data);
}

void				ft_open_window(t_data *data)
{
	void			*mlx_ptr;
	void			*win_ptr;

	if ((mlx_ptr = mlx_init()) == NULL)
		ft_print(ft_msg(ERROR_30));
	if ((win_ptr = mlx_new_window(mlx_ptr, DW, DH, "RTv1")) == NULL)
		ft_print(ft_msg(ERROR_31));
	if ((data->img.img_ptr = mlx_new_image(mlx_ptr, DW, DH)) == NULL)
		ft_print(ft_msg(ERROR_32));
	data->img.img_arr = (int*)mlx_get_data_addr(data->img.img_ptr,
	&data->img.bit_per_pixel, &data->img.size_line, &data->img.endian);
	data->mlx_ptr = mlx_ptr;
	data->win_ptr = win_ptr;
	ft_draw(data);
	ft_clean();
	mlx_hook(win_ptr, 17, 0, ft_close_window, data);
	mlx_hook(win_ptr, 2, 0, ft_key_press, data);
	mlx_loop(mlx_ptr);
}

int					main(int argc, char **argv)
{
	int				fd;
	t_data			data;

	if (argc == 2)
	{
		ft_check_argv(argv[1]);
		ft_open_file(argv[1], &fd);
		ft_init_shapes(&data);
		ft_get_scene(fd, &data);
		ft_close_file(fd);
		ft_check_valid(&data);
		ft_open_window(&data);
	}
	else
		ft_print(USAGE);
	return (0);
}
