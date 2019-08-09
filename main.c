/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 13:37:06 by jwisozk           #+#    #+#             */
/*   Updated: 2019/08/09 16:21:50 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	ft_draw(t_asset *p)
{
	int i;
	int j;

	i = 0;
	while (i < DH)
	{
		j = 0;
		while (j < DW)
		{
			p->img.img_arr[i * DW + j] = 0xFFFFFF;
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