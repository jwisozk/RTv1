/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 16:09:56 by jwisozk           #+#    #+#             */
/*   Updated: 2019/08/09 16:09:56 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int		ft_close_window(t_asset *p)
{
	mlx_destroy_window(p->mlx_ptr, p->win_ptr);
	exit(0);
}

int		ft_key_press(int key, t_asset *p)
{
	if (key == 53)
		ft_close_window(p);
	return (0);
}