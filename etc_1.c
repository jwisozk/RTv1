/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 16:09:56 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/30 08:57:07 by jwisozk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int					ft_print_error(char *str)
{
	void *pass;

	pass = NULL;
	ft_putendl_fd(str, 2);
	ft_clean(pass);
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

t_lst				*ft_new_lst(char *type, void *data)
{
	t_lst			*lst;

	if (!(lst = (t_lst*)ft_malloc(sizeof(t_lst))))
		ft_print_error(ERROR_29);
	lst->type = type;
	lst->data = data;
	lst->next = NULL;
	return (lst);
}

void				ft_add_lst(t_lst **head, t_lst *new)
{
	if (head != NULL && new != NULL)
	{
		new->next = *head;
		*head = new;
	}
}
