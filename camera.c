/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iplastun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 19:51:35 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/24 20:25:42 by iplastun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_cam *ft_create_camera(t_vec3 *f, t_vec3 *l, t_vec3 *u, t_vec3 *pos)
{
    t_cam *cam;

    cam = (t_cam*)malloc(sizeof(t_cam));
    cam->forward = f;
    cam->left = l;
    cam->up = u;
    cam->pos = pos;
    return (cam);
}

static double	ft_map_x(int x, double size, int width)
{
    return (x * size / width - (size / 2));
}

static double	ft_map_y(int y, double size, int height)
{
    return (-y * size / height + (size / 2));
}

void camera_ray(t_data *data, int x, int y)
{
    t_vec3 *new_forw;
    t_vec3 *new_left;
    t_vec3 *new_up;
    t_vec3 *left_up;

    new_left = ft_multiply(ft_map_x(x, VW, DW), data->cam->left);
    new_up = ft_multiply(ft_map_y(y, VH, DH), data->cam->up);
    new_forw = ft_multiply(D, data->cam->forward);
    left_up = ft_add(new_up, new_left);
    data->ray->direct =  ft_normalize_vec3(ft_add(left_up, new_forw));
    data->ray->origin = data->cam->pos;
}

t_cam *ft_camera_look_at(t_vec3 *look_at, t_vec3 *cam_pos)
{
    t_vec3 *forward;
    t_vec3 *left;
    t_vec3 *up;
    t_vec3 *tmp;

    forward = ft_normalize_vec3(ft_subtract(look_at, cam_pos));
    if (forward->x == 0 &&
        (forward->y == 1 || forward->y == -1) &&
        forward->z == 0)
        tmp = ft_create_vec3(0, 0, 1);
    else
        tmp = ft_create_vec3(0, 1, 0);
    left = ft_normalize_vec3(ft_cross_product(tmp, forward));
    up = ft_normalize_vec3(ft_cross_product(forward, left));
    return (ft_create_camera(forward, left, up, cam_pos));
}
