/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 22:04:45 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/29 23:38:44 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GC_H
# define FT_GC_H
# include <stdio.h>
# include <stdlib.h>
# define TGC_OPTIMAL_SIZE (2u<<5u)

typedef struct		s_gc_vector
{
	ssize_t			count;
	ssize_t			len;
	ssize_t			size;
	void			**data;
}					t_gc_vector;
void				ft_gc(t_gc_vector **vector);
void				ft_tgc_append(t_gc_vector **vector, void **d);
t_gc_vector			*init_tgc_vector(ssize_t ssize);
//extern t_gc_vector	*g_memaloced;
#endif