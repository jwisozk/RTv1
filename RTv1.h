/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 13:37:42 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/08 21:22:08 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <math.h>
# include "libft/libft.h"
# include "minilibx/mlx.h"

# define DW 600
# define DH 600
# define HEADER 45
# define VW 1
# define VH 1
# define D 1
# define INF 1000
# define BACKGROUND 93, 176, 200
# define RE_LEN 10

# define ZA 1
# define E 0.001

typedef struct 		s_point
{
	double 			x;
	double 			y;
	double 			z;
}					t_point;

//typedef struct 		s_vector
//{
//	double 			x;
//	double 			y;
//	double 			z;
//}					t_vector;

//typedef struct 		s_object
//{
//	void			*data;
//}					t_object;

typedef  struct 	s_sphere
{
	char 			*str;
	t_point			*center;
	double			radius;
	int				color;
	int			    specular;
	double          closest_t;
	struct s_sphere	*next;
}					t_sphere;

typedef  struct 	s_light
{
	char 			*type;
	double 			intensity;
	t_point 		*position;
	int             n;
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

typedef  struct s_intersect
{
    t_point		*origin;
    t_point		*direct;
    double 		t_min;
    double		t_max;
}               t_intersect;

typedef struct	s_asset
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_sphere	*s;
	t_light		*l;
    t_point		*camera;
    t_point		*direction;
	int 		color;
    double 		t_min;
    double		t_max;
	double 		view_w;
	double 		view_h;
	double 		dwi;
	double 		dhi;
	t_point		*point;
	t_point		*radius;
	t_point		*normal;
	int 		specular;
}				t_asset;

int		ft_key_press(int key, t_asset *p);
int		ft_close_window(t_asset *p);
void	ft_draw(t_asset *p);
t_point	*ft_create_point(double x, double y, double z);
t_sphere *ft_closest_intersection(t_asset *p, t_intersect *i);
double ft_dot(t_point *v1, t_point *v2);
t_point *ft_multiply(double k, t_point *v);
t_point *ft_subtract(t_point *v1, t_point *v2);
t_point *ft_add(t_point *v1, t_point *v2);
int	ft_rgb(int r, int g, int b);
double ft_lenv(t_point *v);
int ft_multiply_color(double k, int color);
double ft_lighting(t_asset *p, t_point *dir, int specular);
t_intersect	*ft_create_intersect(t_point *cam, t_point *dir, double t_min, double t_max);
double ft_max(double x, double y);
double ft_min(double x, double y);
int scene_intersect(t_asset *p);
# include <stdio.h>

#endif
