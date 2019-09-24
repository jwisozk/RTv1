/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iplastun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 13:37:42 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/24 20:44:12 by iplastun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <math.h>
# include "libft/libft.h"
# include "minilibx/mlx.h"

# define DW             600
# define DH             600
# define VW             1
# define VH             1
# define D              1
# define INF            1000
# define BACKGROUND     93, 176, 200


# define E              1e-6
# define OBJ_SPHERE     {SPHERE, &ft_sphere_intersect, &ft_sphere_fill}
# define OBJ_PLANE      {PLANE, &ft_plane_intersect, &ft_plane_fill}
# define OBJ_CYLINDER   {CYLINDER,  &ft_cylinder_intersect, &ft_cylinder_fill}
# define OBJ_CONE   	{CONE,  &ft_cone_intersect, &ft_cone_fill}
# define ARR_OBJ        {OBJ_SPHERE, OBJ_CYLINDER, OBJ_PLANE, OBJ_CONE}
# define ARR_OBJ_NUM    4
# define TANH(x) 		tanh(x * M_PI / 180)
# define COS(x) 		cos(x * M_PI / 180)
# define SIN(x) 		sin(x * M_PI / 180)

typedef struct 			s_vec3
{
	double 				x;
	double 				y;
	double 				z;
}						t_vec3;

typedef struct 			s_vec4
{
	double 				x;
	double 				y;
	double 				z;
	double				k;
}						t_vec4;

typedef struct 			s_ang3
{
    int 				x;
    int 				y;
    int 				z;
}						t_ang3;

typedef  struct s_ray
{
	t_vec3				*origin;
	t_vec3				*direct;
	double 				t_min;
	double				t_max;
    t_ang3              *a;
    t_vec3              *t;
}               		t_ray;

typedef enum 			e_type_obj
{
	SPHERE,
	CYLINDER,
	PLANE,
	CONE
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

typedef  struct 	    s_cone
{
	t_vec3			    *center;
	t_vec3			    *normal;
	double			    angle;
	int				    color;
	int			        specular;
	struct s_cone		*next;
}                       t_cone;

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

typedef  struct 		s_point
{
    t_vec3				*point;
    t_vec3				*normal;
    int 				color;
    int 				specular;
}						t_point;

typedef struct          s_cam
{
    t_vec3              *forward;
    t_vec3              *left;
    t_vec3              *up;
    t_vec3              *pos;
}                       t_cam;

typedef struct			s_data
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_img				img;

    t_obj       		*o;
	t_light				*l;
    t_ray				*ray;
    t_point             *p;

    t_cam               *cam;
}						t_data;

int						ft_key_press(int key, t_data *data);
int						ft_close_window(t_data *data);

void					ft_draw(t_data *data);
double 					ft_lighting(t_point *p, t_light *l, t_obj *o, t_vec3 *vec_po);

t_obj                   *ft_create_object(void *obj, t_type_obj type);
t_sphere                *ft_create_sphere(int color, t_vec3 *center, double radius, int specular);
t_cylinder              *ft_create_cylinder(int color, t_vec3 *center, t_vec3 *normal, double radius, int specular);
t_cone                  *ft_create_cone(int color, t_vec3 *center, t_vec3 *normal, int degree, int specular);
t_plane                 *ft_create_plane(int color, t_vec3 *point, t_vec3* normal, int specular);

t_vec3                  *ft_create_vec3(double x, double y, double z);
t_ang3	                *ft_create_ang3(int x, int y, int z);
t_ray                   *ft_create_ray(t_vec3 *cam, t_vec3 *dir, double t_min, double t_max);
t_light                 *ft_new_light(char *type, double intensity, t_vec3 *position, int n);
t_point	                *ft_create_point(void);

t_obj                   *ft_scene_intersect(t_obj *o, t_ray *ray);
void 					ft_sphere_intersect(t_ray *ray, t_obj *o);
void 					ft_plane_intersect(t_ray *ray, t_obj *o);
void 					ft_cylinder_intersect(t_ray *ray, t_obj *o);
void 					ft_cone_intersect(t_ray *ray, t_obj *o);

void 					ft_sphere_fill(t_obj *obj, t_point *p, t_ray *ray);
void 					ft_cylinder_fill(t_obj *obj, t_point *p, t_ray *ray);
void 					ft_plane_fill(t_obj *obj, t_point *p, t_ray *ray);
void 					ft_cone_fill(t_obj *obj, t_point *p, t_ray *ray);

double 					ft_dot(t_vec3 *v1, t_vec3 *v2);
t_vec3                  *ft_cross_product(t_vec3 *a, t_vec3 *b);
t_vec3                  *ft_multiply(double k, t_vec3 *v);
t_vec3                  *ft_subtract(t_vec3 *v1, t_vec3 *v2);
t_vec3                  *ft_add(t_vec3 *v1, t_vec3 *v2);
double 					ft_lenv(t_vec3 *v);
double 					ft_max(double x, double y);
double 					ft_min(double x, double y);
t_vec3                  *ft_normalize_vec3(t_vec3 *v);

int						ft_rgb(int r, int g, int b);
int 					ft_multiply_color(double k, int color);

t_cam                   *ft_camera_look_at(t_vec3 *look_at, t_vec3 *cam_pos);
t_cam                   *ft_create_camera(t_vec3 *f, t_vec3 *l, t_vec3 *u, t_vec3 *pos);
void                    camera_ray(t_data *data, int x, int y);

//t_vec3*ft_rotate(t_vec3 *v, t_ang3 *a);
//t_vec3*ft_translate(t_vec3* o, t_vec3* t);
//t_vec4*ft_create_vec4(double x, double y, double z);
//t_vec3 *ft_rotate_x(t_vec3 *v, t_ang3 *a);
//t_vec3 *ft_rotate_y(t_vec3 *v, t_ang3 *a);
//t_vec3 *ft_rotate_z(t_vec3 *v, t_ang3 *a);


//t_vec3 *ft_normalize_vec3(t_vec3 *v);

# include <stdio.h>

#endif
