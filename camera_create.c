/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 14:33:05 by iplastun          #+#    #+#             */
/*   Updated: 2019/09/29 20:57:23 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_cam				*ft_create_camera(void)
{
	t_cam *cam;

	if (!(cam = (t_cam*)ft_malloc(sizeof(t_cam))))
		ft_print_error(ERROR_29);
	cam->pos = NULL;
	cam->look_at = NULL;
	cam->forward = NULL;
	cam->left = NULL;
	cam->up = NULL;
	return (cam);
}
