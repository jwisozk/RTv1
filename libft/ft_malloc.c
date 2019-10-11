/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iplastun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 17:22:53 by jwisozk           #+#    #+#             */
/*   Updated: 2019/10/11 14:47:18 by iplastun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(size_t size)
{
	void			*memory;
	static t_gc		*vector = NULL;

	memory = NULL;
	if (size == 0)
	{
		ft_gc_clean(&vector);
		return (NULL);
	}
	if (!vector)
		vector = ft_gc_create();
	memory = malloc(size);
	ft_bzero(memory, size);
	ft_gc_add(&vector, memory);
	return (memory);
}
