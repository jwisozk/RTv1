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
# define INF 1000
# define BACKGROUND 93, 176, 200
# define RE_LEN 10

# define ZA 1
# define E 1e-6

# define OBJ_SPHERE      {SPHERE, &ft_sphere_intersect, &ft_sphere_fill}
# define OBJ_PLANE       {PLANE, &ft_plane_intersect, &ft_plane_fill}
# define OBJ_CYLINDER    {CYLINDER,  &ft_cylinder_intersect, &ft_cylinder_fill}
# define ARR_OBJ         {OBJ_SPHERE, OBJ_CYLINDER, OBJ_PLANE}
# define ARR_OBJ_NUM     3

typedef struct 			s_vec3
{
	double 				x;
	double 				y;
	double 				z;
}						t_vec3;

typedef  struct s_ray
{
	t_vec3				*origin;
	t_vec3				*direct;
	double 				t_min;
	double				t_max;
}               		t_ray;

typedef enum 			e_type_obj
{
	SPHERE,
	CYLINDER,
	PLANE
}						t_type_obj;

typedef struct          s_arr_obj
{
	t_type_obj          type;
	void 				(*ft_obj_intersect)();
	void 				(*ft_obj_fill)();
}                       t_arr_obj;

typedef struct 			s_obj
{
	t_type_obj			type;
	void				*obj;
	void				*objects;
	double              t;
	struct s_obj		*next;

}						t_obj;

typedef  struct 	    s_sphere
{
	t_vec3			    *center;
	double			    radius;
	int				    color;
	int			        specular;
	struct s_sphere	    *next;
}					    t_sphere;

typedef  struct 	    s_cylinder
{
    t_vec3			    *center;
    t_vec3			    *normal;
    double			    radius;
    int				    color;
    int			        specular;
    struct s_cylinder	*next;
}                       t_cylinder;

typedef  struct		    s_plane
{
	t_vec3			    *normal;
	t_vec3			    *point;
	int 			    color;
	int				    specular;
	struct s_plane	    *next;
}					    t_plane;

typedef  struct 		s_light
{
	char 				*type;
	double 				intensity;
	t_vec3 		   		*position;
	int            		n;
	struct s_light		*next;
}						t_light;

typedef struct			s_img
{
	int					bit_per_pixel;
	int					size_line;
	int					endian;
	void				*img_ptr;
	int					*img_arr;
}						t_img;

typedef struct			s_asset
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_img				img;
    t_obj       		*o;
	t_sphere			*s;
	t_plane				*p;
	t_cylinder 			*c;
	t_light				*l;
	int 				color;
	double 				view_w;
	double 				view_h;
	double 				dwi;
	double 				dhi;
	t_vec3				*point;
	t_vec3				*radius;
	t_vec3				*normal;
	int 				specular;
	t_ray				*ray;
	int 				j;
}						t_asset;

int						ft_key_press(int key, t_asset *p);
int						ft_close_window(t_asset *p);

void					ft_draw(t_asset *p);
double 					ft_lighting(t_asset *p, t_vec3 *dir, int specular);

t_vec3*					ft_create_vec3(double x, double y, double z);
t_obj*					ft_create_object(void *obj, t_type_obj type);
t_ray					*ft_create_ray(t_vec3 *cam, t_vec3 *dir, double t_min, double t_max);

int 					ft_scene_intersect(t_asset *p);
void 					ft_sphere_intersect(t_ray *ray, t_obj *o);
void 					ft_plane_intersect(t_ray *ray, t_obj *o);
void 					ft_cylinder_intersect(t_ray *ray, t_obj *o);

void 					ft_sphere_fill(t_obj *obj, t_asset *p);
void 					ft_cylinder_fill(t_obj *obj, t_asset *p);
void 					ft_plane_fill(t_obj *obj, t_asset *p);

double 					ft_dot(t_vec3 *v1, t_vec3 *v2);
t_vec3 					*ft_multiply(double k, t_vec3 *v);
t_vec3 					*ft_subtract(t_vec3 *v1, t_vec3 *v2);
t_vec3 					*ft_add(t_vec3 *v1, t_vec3 *v2);
double 					ft_lenv(t_vec3 *v);
double 					ft_max(double x, double y);
double 					ft_min(double x, double y);

int						ft_rgb(int r, int g, int b);
int 					ft_multiply_color(double k, int color);



//t_vec3 *ft_normalize_vec3(t_vec3 *v);

# include <stdio.h>

#endif
