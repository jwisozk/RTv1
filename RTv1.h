/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 13:37:42 by jwisozk           #+#    #+#             */
/*   Updated: 2019/08/26 20:47:14 by jwisozk          ###   ########.fr       */
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
# define VW 1
# define VH 1
# define D 1
# define INF 1000
# define BACKGROUND 93, 176, 200
# define RE_LEN 10

# define ZA 1
# define max(x, y) ( (x) > (y) ? (x) : (y) )
# define min(x, y) ( (x) < (y) ? (x) : (y) )

typedef struct 		s_point
{
	double 			x;
	double 			y;
	double 			z;
}					t_point;

typedef struct 		s_vector
{
	double 			x;
	double 			y;
	double 			z;
}					t_vector;

typedef struct 		s_object
{
	void			*data;
}					t_object;

typedef struct 		s_color
{
	int				r;
	int 			g;
	int 			b;
}					t_color;

typedef  struct 	s_sphere
{
	char 			*str;
	t_point			*center;
	double			radius;
	t_color			*color;
	struct s_sphere	*next;
}					t_sphere;

typedef  struct 	s_light
{
	char 			*type;
	double 			intensity;
	t_point 		*position;
	struct s_light	*next;
}					t_light;


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
	t_light		*l;
	t_point		*camera;
	t_point		*direction;
	t_color 	*color;
	double 		view_w;
	double 		view_h;
	double 		dwi;
	double 		dhi;
	double 		t_min;
	double		t_max;
}				t_asset;

int		ft_key_press(int key, t_asset *p);
int		ft_close_window(t_asset *p);
void	ft_draw(t_asset *p);
t_point	*ft_create_point(double x, double y, double z);

double ft_dot(t_point *v1, t_point *v2);
double ft_length_vector(t_point *v1, t_point *v2);
t_point *ft_multiply(double k, t_point *v);
t_point *ft_subtract(t_point *v1, t_point *v2);
t_point *ft_add(t_point *v1, t_point *v2);
double ft_compute_lighting(t_point *point, t_point* normal, t_asset *p);
t_point	*ft_convert_ctop(t_color *color);
t_color	*ft_convert_ptoc(t_point *point);
int	ft_rgb(unsigned char r, unsigned char g, unsigned char b);
t_color *ft_rgb_rev(int r, int g, int b);
int ft_clamp(t_color *v);
# include <stdio.h>

#endif
