/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:37:26 by jwisozk           #+#    #+#             */
/*   Updated: 2019/08/28 14:21:24 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int	ft_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int ft_multiply_color(double k, int color)
{
	int r;
	int g;
	int b;

	r = min(255, max(0, (color >> 16 & 255) * k));
	g = min(255, max(0, (color >> 8 & 255) * k));
	b = min(255, max(0, (color & 255) * k));
	return (ft_rgb(r, g, b));
}

