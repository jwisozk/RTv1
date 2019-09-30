/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 17:05:02 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/30 17:05:02 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_light				*ft_create_light(t_data *data)
{
	t_light			*l;

	if (!(l = (t_light*)ft_malloc(sizeof(t_light))))
		ft_print_error(ERROR_29);
	l->type = NULL;
	l->position = NULL;
	l->intensity = -1;
	l->next = data->l != NULL ? data->l : NULL;
	return (l);
}
