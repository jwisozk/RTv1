/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:23:15 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/12 23:39:13 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_vec3	*ft_display_to_view(int x, int y, t_asset *p)
{
	t_vec3 *d;

	d = ft_create_vec3(x * p->view_w * p->dwi, -y * p->view_h * p->dhi, ZA);
	return (d);
}

t_obj	*ft_find_closest_obj(t_obj* obj, t_ray* ray)
{
	static t_arr_obj arr[ARR_OBJ_NUM] = ARR_OBJ;

	int i = 0;
	while (i < ARR_OBJ_NUM)
	{
		if (arr[i].type == obj->type)
		{
			obj->t = INF;

			arr[i].ft_obj_intersect(ray, obj);
			return (obj);
		}
		i++;
	}
	return (NULL);
}

int ft_obj_fill(t_obj *obj, t_asset *p)
{
	static t_arr_obj arr[ARR_OBJ_NUM] = ARR_OBJ;

	int i = 0;
	while (i < ARR_OBJ_NUM)
	{
		if (arr[i].type == obj->type)
		{
			arr[i].ft_obj_fill(obj, p);
		}
		i++;
	}
	return (1);
}


int		ft_scene_intersect(t_asset *p)
{
	t_obj *obj_loop;
	t_obj *obj;
	t_obj *new_obj;
	double t;

	obj_loop = p->o;
	t = INF;
	obj = NULL;
	while (obj_loop != NULL)
	{

		new_obj = ft_find_closest_obj(obj_loop, p->ray);
		if (new_obj != NULL && new_obj->t < t)
		{
			if(obj != NULL)
			{
//				free(obj->obj);
//				free(obj);
			}
			t = new_obj->t;
			obj = new_obj;
		}
		obj_loop = obj_loop->next;
	}
	if (obj != NULL)
		return (ft_obj_fill(obj, p));
	return (0);

}

int ft_trace_ray(t_asset *p)
{
	t_vec3 *vec_po;

	if (ft_scene_intersect(p) == 0)
		return ft_rgb(BACKGROUND);
	vec_po = ft_multiply(-1, p->ray->direct);
	double lighting = ft_lighting(p, vec_po, p->specular);
	return (ft_multiply_color(lighting, p->color));
}

void	ft_draw(t_asset *p)
{
	int 	i;
	int		j;
	int 	offset_x;
    int     offset_y;

	offset_x = (int)(DW * 0.5);
	offset_y = (int)(DH * 0.5);
	i = 0;
	while (i < DH)
	{
		j = 0;
		while (j < DW)
		{
//			p->j = j;
//			printf("%i\n", j);
			p->ray->direct = ft_display_to_view(j - offset_x, i - offset_y, p);
			p->color = ft_trace_ray(p);
			p->img.img_arr[i * DW + j] = p->color;
			j++;

		}

		i++;
	}
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img.img_ptr, 0, 0);
}

