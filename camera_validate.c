/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 19:01:12 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/29 15:34:39 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void				ft_check_camera(t_data *data)
{
	t_vec3			*a;
	t_vec3			*b;

	if (data->cam == NULL)
		ft_print_error(ft_msg(ERROR_7), data->ptr_mem);
	a = data->cam->look_at;
	b = data->cam->pos;
	if (a == NULL)
		ft_print_error(ft_msg(ERROR_8), data->ptr_mem);
	if (b == NULL)
		ft_print_error(ft_msg(ERROR_9), data->ptr_mem);
	if (a->x == b->x &&
		a->y == b->y &&
		a->z == b->z)
		ft_print_error(ft_msg(ERROR_10), data->ptr_mem);
}
