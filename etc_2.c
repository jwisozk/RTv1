/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk  <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 17:05:28 by jwisozk           #+#    #+#             */
/*   Updated: 2019/10/11 13:24:43 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char				*ft_msg(char *str)
{
	return (ft_strjoin(ERROR, str));
}

void				ft_check_argv(char *str)
{
	char 	*ext1;
	char 	*ext2;
	
	if (ft_strequ(str, "foto4ka"))
	{
		void			*mlx_ptr;
		void			*win_ptr;
		int				width;
		int				height;
		width = 1000;
		height = 667;
		if ((mlx_ptr = mlx_init()) == NULL)
			ft_print_error(ft_msg(ERROR_30));
		if ((win_ptr = mlx_new_window(mlx_ptr, width, height, "R4Y7r4c1N9_C4P031R4")) == NULL)
			ft_print_error(ft_msg(ERROR_31));
		void *ptr = mlx_xpm_file_to_image(mlx_ptr, ".foto4ka", &width, &height);
		mlx_put_image_to_window(mlx_ptr, win_ptr, ptr, 0, 0);
//		mlx_hook(win_ptr, 17, 0, ft_close_window, data);
//		mlx_hook(win_ptr, 2, 0, ft_key_press, data);
		mlx_loop(mlx_ptr);
	}
	ext1 = ft_strrev(str);
	ext2 = ft_strrev(EXTENSION);
	if (ft_strnequ(ext1, ext2, 4) != 1)
		ft_print_error(ft_msg(ERROR_1));
}

void				ft_open_file(char *name, int *fd)
{
	if ((*fd = open(name, O_RDONLY)) == -1)
		ft_print_error(ft_msg(ERROR_6));
}

void				ft_close_file(const int fd)
{
	if (close(fd) == -1)
		ft_print_error(ft_msg(ERROR_28));
}