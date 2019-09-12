/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 13:37:42 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/12 23:01:13 by jwisozk          ###   ########.fr       */
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
# define E 1e-6

typedef struct 		s_vec3
{
	double 			x;
	double 			y;
	double 			z;
}					t_vec3;

//typedef struct 		s_object
//{
//	void			*data;
//}					t_object;

typedef  struct 	s_sphere
{
	char 			*str;
	t_vec3			*center;
	double			radius;
	int				color;
	int			    specular;
	double          t;
	struct s_sphere	*next;
}					t_sphere;

typedef  struct		s_plane
{
	t_vec3			*normal;
	t_vec3			*point;
	int 			color;
	int				specular;
	double          t;
	struct s_plane	*next;
}					t_plane;


typedef  struct 	s_light
{
	char 			*type;
	double 			intensity;
	t_vec3 		*position;
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

typedef  struct s_ray
{
    t_vec3		*origin;
    t_vec3		*direct;
    double 		t_min;
    double		t_max;
    void		*obj;
}               t_ray;

typedef struct	s_asset
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_sphere	*s;
	t_plane		*p;
	t_light		*l;
	int 		color;
	double 		view_w;
	double 		view_h;
	double 		dwi;
	double 		dhi;
	t_vec3		*point;
	t_vec3		*radius;
	t_vec3		*normal;
	int 		specular;
	t_ray		*ray;
}				t_asset;

int		ft_key_press(int key, t_asset *p);
int		ft_close_window(t_asset *p);
void	ft_draw(t_asset *p);
t_vec3	*ft_create_point(double x, double y, double z);
t_sphere *ft_sphere_intersect(t_ray *ray);
double ft_dot(t_vec3 *v1, t_vec3 *v2);
t_vec3 *ft_multiply(double k, t_vec3 *v);
t_vec3 *ft_subtract(t_vec3 *v1, t_vec3 *v2);
t_vec3 *ft_add(t_vec3 *v1, t_vec3 *v2);
int	ft_rgb(int r, int g, int b);
double ft_lenv(t_vec3 *v);
int ft_multiply_color(double k, int color);
double ft_lighting(t_asset *p, t_vec3 *dir, int specular);
t_ray	*ft_create_ray(t_vec3 *cam, t_vec3 *dir, double t_min, double t_max);
double ft_max(double x, double y);
double ft_min(double x, double y);
int ft_scene_intersect(t_asset *p);
t_plane *ft_plane_intersect(t_ray *ray, t_plane *pl);
# include <stdio.h>

#endif
