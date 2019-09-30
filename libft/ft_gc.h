/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iplastun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 22:04:45 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/30 08:50:03 by iplastun         ###   ########.fr       */
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

#endif