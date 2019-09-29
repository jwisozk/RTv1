/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 14:44:38 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/29 17:04:06 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_lst *ft_new_lst(char *type, void *data)
{
	t_lst *lst;

	lst = (t_lst*)malloc(sizeof(t_lst));
	lst->type = type;
	lst->data = data;
	lst->next = NULL;
	return (lst);
}

void  ft_add_lst(t_lst **head, t_lst *new)
{
	if (head != NULL && new != NULL)
	{
		new->next = *head;
		*head = new;
	}
}

void	ft_check_braces(int *block, int n)
{
	int err;

	err = 0;
	if (*block > 0 && n == 1)
		err = 1;
	if (*block == 0 && n == 2)
		err = 1;
	if (*block != 0 && n == 3)
		err = 1;
	if (n == 1)
		(*block)++;
	if (n == 2)
		(*block)--;
	if (err == 1)
		ft_print_error(ft_msg(ERROR_3));
}

int ft_is_hash(char *line, int *i, t_arr_type *arr, int max)
{

	char 	*type;

	if (*line != '#')
		return (0);

	type = ft_strsplit(line + 1, ' ')[0];
	*i = 0;
	while (*i < max && ft_strequ(type, arr[*i].type) != 1)
		(*i)++;
	if (*i == max)
		ft_print_error(ft_msg(ERROR_2));
	return (1);
}

void ft_get_scene(int fd, t_data *data)
{
	char	*line;
	int		i;
	int 	j;
	char	**str;
//	char 	*type;
	static t_arr_type arr[] = ARR_TYPES;
	int 	max;
	t_lst	*lst;
	t_lst	*tmp;
	int 	block;

	lst = NULL;
	block = 0;
	max = sizeof(arr) / sizeof(t_arr_type);
	while (get_next_line(fd, &line) > 0)
	{
		while (ft_isspace(*line) == 1)
			line++;
		if (*line == '\0')
			continue ;
		if (ft_is_hash(line, &i, arr, max) == 1)
			continue ;
		if (*line == '{')
			ft_check_braces(&block, 1);
		else if (*line == '}')
		{
			if (lst != NULL)
				arr[i].ft_create_type(data, lst);
			lst = NULL;
			ft_check_braces(&block, 2);
		}
		else if (block == 1 && (str = ft_strsplit(line, ' '))[0] != NULL)
		{
			j = 0;
			while (str[j] != NULL)
				j++;
			if (j == 2)
				tmp = ft_new_lst(str[0], str[1]);
			else if (j == 5 && ft_strequ(str[0], ROTATION))
				tmp = ft_new_lst(str[0], ft_new_arr_i(str[1], str[2], str[3], str[4]));
			else if (ft_strequ(str[0], COLOR) || ft_strequ(str[0], ROTATION))
				tmp = ft_new_lst(str[0], ft_new_arr_i(str[1], str[2], str[3], NULL));
			else
				tmp = ft_new_lst(str[0], ft_new_arr_d(str[1], str[2], str[3]));
			ft_add_lst(&lst, tmp);
		}
	}
	ft_check_braces(&block, 3);
	ft_create_scene_objects(data);
}