/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 17:22:53 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/30 17:22:53 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(size_t size)
{
	void					*ch;
	static t_gc_vector		*memalloced = NULL;

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
