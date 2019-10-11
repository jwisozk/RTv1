/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iplastun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 16:14:01 by jwisozk           #+#    #+#             */
/*   Updated: 2019/10/10 22:55:03 by iplastun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_free_all(void **ptr, int len)
{
	if (ptr != NULL)
	{
		while (len--)
			ft_memdel(&ptr[len]);
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}
