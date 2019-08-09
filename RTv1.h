/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 13:37:42 by jwisozk           #+#    #+#             */
/*   Updated: 2019/08/09 15:54:19 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <math.h>
# include "libft/libft.h"
# include "minilibx/mlx.h"

# define DW 1600
# define DH 855
# define HEADER 45

typedef struct 	s_point
{
	float x;
	float y;
	float z;
}				t_point;

typedef struct 	s_line
{
	t_point start;
	t_point	end;
}				t_line;

typedef struct	s_img
{
	int			bit_per_pixel;
	int			size_line;
	int			endian;
	void		*img_ptr;
	int			*img_arr;
}				t_img;

typedef struct	s_asset
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
}				t_asset;

int		ft_key_press(int key, t_asset *p);
int		ft_close_window(t_asset *p);
# include <stdio.h>

#endif
