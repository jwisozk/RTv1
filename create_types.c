/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 14:33:05 by iplastun          #+#    #+#             */
/*   Updated: 2019/09/28 20:10:39 by jwisozk          ###   ########.fr       */
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
		else if (ft_strequ(lst->type, "look_at") == 1)
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
	l->intensity = -1;
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
		else if (ft_strequ(lst->type, "position") == 1)
		{
			d = (double*)lst->data;
			l->position = ft_create_vec3(d[0], d[1], d[2]);
		}
		lst = lst->next;
	}
	data->l = l;
}

