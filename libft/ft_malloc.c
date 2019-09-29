/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 22:01:44 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/29 22:38:10 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(size_t size, t_gc_vector *ptr_mem)
{
	void *ch;
//	t_gc_vector *g_memaloced;
//
//	g_memaloced = NULL;
	t_gc_vector *memaloced;

	memaloced = ptr_mem;
	ch = NULL;
	if (!memaloced)
		memaloced = init_tgc_vector(sizeof(size_t *));
	ch = malloc(size);
	ft_bzero(ch, size);
	if (ch == NULL)
		exit(3);
	ft_tgc_append(&memaloced, ch);
	return (ch);
}