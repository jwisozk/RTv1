/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 16:43:23 by jwisozk           #+#    #+#             */
/*   Updated: 2018/12/16 16:38:01 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//void	*ft_memalloc(size_t size)
//{
//	unsigned char	*s;
//
//	if (size + 1 == 0)
//		return (NULL);
//	s = (unsigned char*)malloc(sizeof(*s) * size);
//	if (!s)
//		return (NULL);
//	ft_bzero(s, size);
//	return (s);
//}

t_gc_vector *g_memaloced = NULL;

void	*ft_memalloc(size_t size)
{
	void *ch;

	ch = NULL;
	if (!g_memaloced)
		g_memaloced = init_tgc_vector(sizeof(size_t *));
	ch = malloc(size);
	ft_bzero(ch, size);
	if (ch == NULL)
		exit(3);
	ft_tgc_append(&g_memaloced, ch);
	return (ch);
}