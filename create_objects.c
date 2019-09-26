/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iplastun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 20:31:01 by iplastun          #+#    #+#             */
/*   Updated: 2019/09/25 18:46:08 by iplastun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_obj *ft_create_object(void *obj, t_type_obj type)
{
    t_obj *o;

    o = (t_obj*)malloc(sizeof(t_obj));
    o->type = type;
    o->objects = obj;
    o->obj = NULL;
    o->t = INF;
    o->next = NULL;
    return (o);
}

