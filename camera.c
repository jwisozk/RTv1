/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iplastun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 19:51:35 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/27 00:24:33 by iplastun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static double	ft_map_x(int x, double size, int width)
{
    return (x * size / width - (size / 2));
}

static double	ft_map_y(int y, double size, int height)
{
    return (-y * size / height + (size / 2));
}

void ft_camera_ray(t_data *data, int x, int y)
{
    t_vec3 *new_forw;
    t_vec3 *new_left;
    t_vec3 *new_up;
    t_vec3 *left_up;

    new_left = ft_multiply(ft_map_x(x, VW, DW), data->cam->left);
    new_up = ft_multiply(ft_map_y(y, VH, DH), data->cam->up);
    new_forw = ft_multiply(D, data->cam->forward);
    left_up = ft_add(new_up, new_left);
    data->ray = ft_create_ray(NULL, NULL, 1, INF);
    data->ray->direct =  ft_normalize_vec3(ft_add(left_up, new_forw));
    data->ray->origin = data->cam->pos;
}

int ft_compare_vec(t_data *data)
{
    t_vec3 *a;
    t_vec3 *b;
    if (data->cam == NULL)
        data->cam = ft_create_camera();
    a = data->cam->look_at;
    b = data->cam->pos;
    if(a == NULL)
        a = ft_create_vec3(0, 0, 0);
    if (b == NULL)
        b = ft_create_vec3(0, 0, -2);
    data->cam->look_at = a;
    data->cam->pos = b;
    if (a->x == b->x &&
        a->y == b->y &&
        a->z == b->z)
        return (1);
    return (0);
}

void ft_camera_look_at(t_data *data)
{
    t_vec3 *forward;
    t_vec3 *left;
    t_vec3 *up;
    t_vec3 *tmp;

    if(ft_compare_vec(data) == 1)
        data->cam->pos->z -= 1;
    forward = ft_normalize_vec3(ft_subtract(data->cam->look_at, data->cam->pos));
    if (forward->x == 0 &&
        (forward->y == 1 || forward->y == -1) &&
        forward->z == 0)
        tmp = ft_create_vec3(0, 0, 1);
    else
        tmp = ft_create_vec3(0, 1, 0);
    left = ft_normalize_vec3(ft_cross_product(tmp, forward));
    up = ft_normalize_vec3(ft_cross_product(forward, left));
    data->cam->forward = forward;
    data->cam->up = up;
    data->cam->left = left;
}
