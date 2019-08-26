/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:37:26 by jwisozk           #+#    #+#             */
/*   Updated: 2019/08/26 20:37:26 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int	ft_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	return ((r << 16) | (g << 8) | b);
}


int ft_clamp(t_color *v)
{
	return(ft_rgb(min(255, max(0, v->r)), min(255, max(0, v->g)), min(255, max(0, v->b))));
}

t_color *ft_rgb_rev(int r, int g, int b)
{
	t_color *c;

	c = (t_color*)malloc(sizeof(t_color));
	c->r = r;
	c->g = g;
	c->b = b;
	return (c);
}

