/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iplastun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 17:05:28 by jwisozk           #+#    #+#             */
/*   Updated: 2019/10/11 13:24:43 by iplastun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char				*ft_msg(char *str)
{
	return (ft_strjoin(ERROR, str));
}

void				ft_check_argv(char *str)
{
	char 	*ext1;
	char 	*ext2;

	ext1 = ft_strrev(str);
	ext2 = ft_strrev(EXTENSION);
	if (ft_strnequ(ext1, ext2, 4) != 1)
	{
//		ft_strdel(&ext1);
//		ft_strdel(&ext2);
		ft_print_error(ft_msg(ERROR_1));
	}
//	ft_strdel(&ext1);
//	ft_strdel(&ext2);
}

void				ft_open_file(char *name, int *fd)
{
	if ((*fd = open(name, O_RDONLY)) == -1)
		ft_print_error(ft_msg(ERROR_6));
}

void				ft_close_file(const int fd)
{
	if (close(fd) == -1)
		ft_print_error(ft_msg(ERROR_28));
}