/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iplastun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 14:33:05 by iplastun          #+#    #+#             */
/*   Updated: 2019/09/26 13:34:59 by iplastun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_cam *ft_create_camera(void)
{
    t_cam *cam;

    cam = (t_cam*)malloc(sizeof(t_cam));
	cam->pos = NULL;
	cam->look_at = NULL;
	cam->forward = NULL;
	cam->left = NULL;
	cam->up = NULL;
    return (cam);
}

void	ft_update_camera(t_data *data, t_lst* lst)
{
	t_cam 		*cam;
	double		*d;

	cam = ft_create_camera();
	while (lst != NULL)
	{
		d = (double*)lst->data;
		if (ft_strequ(lst->type, "position") == 1)
			cam->pos = ft_create_vec3(d[0], d[1], d[2]);
		else
			cam->look_at = ft_create_vec3(d[0], d[1], d[2]);
		lst = lst->next;
	}
	data->cam = cam;
}

t_light *ft_create_light(t_data *data)
{
	t_light *l;

	l = (t_light*)malloc(sizeof(t_light));
	l->type = NULL;
	l->position = NULL;
	l->intensity = 0.0;
	l->next = data->l != NULL ? data->l : NULL;
	return (l);
}

void	ft_update_light(t_data *data, t_lst* lst)
{
	t_light 	*l;
	double		*d;

	l = ft_create_light(data);
	while (lst != NULL)
	{
		if (ft_strequ(lst->type, "type") == 1)
			l->type = (char*)lst->data;
		else if (ft_strequ(lst->type, "intensity") == 1)
			l->intensity = ft_atof((char*)lst->data);
		else
		{
			d = (double*)lst->data;
			l->position = ft_create_vec3(d[0], d[1], d[2]);
		}
		lst = lst->next;
	}
	data->l = l;
}

t_sphere *ft_create_sphere(t_data *data)
{
	t_sphere *s;

	s = (t_sphere*)malloc(sizeof(t_sphere));
	s->center = NULL;
	s->color = 0;
	s->radius = 0.0;
	s->specular = 0;
	s->next = data->sphere != NULL ? data->sphere : NULL;
	return (s);
}

void 	ft_update_sphere(t_data *data, t_lst* lst)
{
	t_sphere 	*s;
	double		*d;
	int 		*i;

	s = ft_create_sphere(data);
	while (lst != NULL)
	{
		if (ft_strequ(lst->type, "center") == 1)
		{
			d = (double*)lst->data;
			s->center = ft_create_vec3(d[0], d[1], d[2]);
		}
		else if (ft_strequ(lst->type, "color") == 1)
		{
			i = (int*)lst->data;
			s->color = ft_rgb(i[0], i[1], i[2]);
		}
		else if (ft_strequ(lst->type, "radius"))
			s->radius = ft_atof((char*)lst->data);
		else
			s->specular = ft_atoi((char*)lst->data);
		lst = lst->next;
	}
	data->sphere = s;
}

t_plane *ft_create_plane(t_data *data)
{
	t_plane *p;

	p = (t_plane*)malloc(sizeof(t_plane));
	p->color = 0;
	p->normal = NULL;
	p->point = NULL;
	p->specular = 0;
	p->next = data->plane != NULL ? data->plane : NULL;
	return (p);
}

void 	ft_update_plane(t_data *data, t_lst* lst)
{
	t_plane 	*p;
	double		*d;

	p = ft_create_plane(data);
	while (lst != NULL)
	{
		if (ft_strequ(lst->type, "color") == 1)
			p->color = ft_rgb(((int*)lst->data)[0], ((int*)lst->data)[1],
					((int*)lst->data)[2]);
		else if (ft_strequ(lst->type, "specular") == 1)
			p->specular = ft_atoi((char*)lst->data);
		else
		{
			d = (double*)lst->data;
			if (ft_strequ(lst->type, "point") == 1)
				p->point = ft_create_vec3(d[0], d[1], d[2]);
			else if (ft_strequ(lst->type, "normal"))
				p->normal = ft_create_vec3(d[0], d[1], d[2]);
		}
		lst = lst->next;
	}
	data->plane = p;
}

t_cylinder *ft_create_cylinder(t_data *data)
{
	t_cylinder *c;

	c = (t_cylinder*)malloc(sizeof(t_cylinder));
	c->center = NULL;
	c->normal = NULL;
	c->color = 0;
	c->radius = 0.0;
	c->specular = 0;
	c->next = data->cylinder != NULL ? data->cylinder : NULL;
	return (c);
}

void 		ft_update_cylinder(t_data *data, t_lst* lst)
{
	t_cylinder 	*c;
	double		*d;

	c = ft_create_cylinder(data);
	while (lst != NULL)
	{
		if (ft_strequ(lst->type, "color") == 1)
			c->color = ft_rgb(((int*)lst->data)[0], ((int*)lst->data)[1],
							  ((int*)lst->data)[2]);
		else if (ft_strequ(lst->type, "specular") == 1)
			c->specular = ft_atoi((char*)lst->data);
		else if (ft_strequ(lst->type, "radius"))
			c->radius = ft_atof((char*)lst->data);
		else
		{
			d = (double*)lst->data;
			if (ft_strequ(lst->type, "center") == 1)
				c->center = ft_create_vec3(d[0], d[1], d[2]);
			else if (ft_strequ(lst->type, "normal"))
				c->normal = ft_create_vec3(d[0], d[1], d[2]);
		}
		lst = lst->next;
	}
	data->cylinder = c;
}

t_cone *ft_create_cone(t_data *data)
{
	t_cone *c;

	c = (t_cone*)malloc(sizeof(t_cone));
	c->center = NULL;
	c->normal = NULL;
	c->color = 0;
	c->angle = TANH(30);
	c->specular = 0;
	c->next = data->cone != NULL ? data->cone : NULL;
	return (c);
}

void 					ft_update_cone(t_data *data, t_lst* lst)
{
	t_cone 		*c;
	double		*d;

	c = ft_create_cone(data);
	while (lst != NULL)
	{
		if (ft_strequ(lst->type, "color") == 1)
			c->color = ft_rgb(((int*)lst->data)[0], ((int*)lst->data)[1],
							  ((int*)lst->data)[2]);
		else if (ft_strequ(lst->type, "specular") == 1)
			c->specular = ft_atoi((char*)lst->data);
		else if (ft_strequ(lst->type, "angle"))
			c->angle = ft_atof((char*)lst->data);
		else
		{
			d = (double*)lst->data;
			if (ft_strequ(lst->type, "center") == 1)
				c->center = ft_create_vec3(d[0], d[1], d[2]);
			else if (ft_strequ(lst->type, "normal"))
				c->normal = ft_create_vec3(d[0], d[1], d[2]);
		}
		lst = lst->next;
	}
	c->next = data->cone != NULL ? data->cone : NULL;
	data->cone = c;
}


