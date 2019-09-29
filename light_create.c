/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 15:28:14 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/29 15:29:06 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

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

