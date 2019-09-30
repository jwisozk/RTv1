/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iplastun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 22:01:44 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/30 08:50:03 by iplastun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(size_t size)
{
	void *ch;
	static t_gc_vector *memalloced = NULL;

	ch = NULL;
	if (!memalloced)
		memalloced = init_tgc_vector(sizeof(size_t *));
	ch = malloc(size);
	ft_bzero(ch, size);
	if (ch == NULL)
		ft_gc(&memalloced);
	else
		ft_tgc_append(&memalloced, ch);
	return (ch);
}
