/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 13:37:42 by jwisozk           #+#    #+#             */
/*   Updated: 2019/08/17 14:33:51 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <math.h>
# include "libft/libft.h"
# include "minilibx/mlx.h"

# define DW 1600
# define DH 854
# define HEADER 46
# define VW 1
# define VH 1
# define D 1
# define INF 1000
# define BACKGROUND 93, 176, 200
# define RE_LEN 10

# define Z 1


typedef struct 		s_point
{
	double 			x;
	double 			y;
	double 			z;
}					t_point;

//typedef struct		s_color
//{
//	unsigned char	r;
//	unsigned char 	g;
//	unsigned char 	b;
//}					t_color;


typedef  struct 	s_sphere
{
	char 			*str;
	t_point			*center;
	double			radius;
	int				color;
	struct s_sphere	*next;
}					t_sphere;


//
//typedef struct 	s_point
//{
//	double x;
//	double y;
//	double z;
//}				t_point;
//
//typedef struct 	s_line
//{
//	t_point start;
//	t_point	end;
//}				t_line;

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
	t_sphere	*s;
	t_point		*camera;
	t_point		*direction;
	int 		color;
	double 		view_w;
	double 		view_h;
	double 		dwi;
	double 		dhi;
	double 		t_min;
	double		t_max;
}				t_asset;

int		ft_key_press(int key, t_asset *p);
int		ft_close_window(t_asset *p);
# include <stdio.h>

#endif
