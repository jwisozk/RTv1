/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 16:09:56 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/29 23:07:48 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

char				*ft_msg(char *str)
{
	return (ft_strjoin(ERROR, str));
}

int					ft_print_error(char *str, t_gc_vector *ptr_mem)
{
	if (ptr_mem != NULL)
		ft_gc(&ptr_mem);
	ft_putendl_fd(str, 2);
	exit(0);
}

int					ft_close_window(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
}

int					ft_key_press(int key, t_data *data)
{
	if (key == 53)
		ft_close_window(data);
	return (0);
}
