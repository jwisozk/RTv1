/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 13:37:06 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/29 15:07:36 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

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

	mlx_ptr = mlx_init();
	// добавить защиту для mlx
	win_ptr = mlx_new_window(mlx_ptr, DW, DH, "RTv1");
	data->img.img_ptr = mlx_new_image(mlx_ptr, DW, DH);
	data->img.img_arr = (int*)mlx_get_data_addr(data->img.img_ptr,
	&data->img.bit_per_pixel, &data->img.size_line, &data->img.endian);
	data->mlx_ptr = mlx_ptr;
	data->win_ptr = win_ptr;
	ft_draw(data);
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
		if (ft_strnequ(ft_strrev(argv[1]), ft_strrev(EXTENSION), 4) != 1)
			ft_print_error(ft_msg(ERROR_1));
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			return (ft_print_error(ft_msg(ERROR_6)));
		ft_init_shapes(&data);
		ft_get_scene(fd, &data);
		if (close(fd) == -1)
			return (ft_print_error(ft_msg(ERROR_28)));
		ft_check_valid(&data);
		ft_open_window(&data);
	}
	else
		ft_print_error("Usage: ./RTv1 <filename>");
	return (0);
}
