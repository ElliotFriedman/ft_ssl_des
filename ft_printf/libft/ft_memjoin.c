/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 09:05:40 by efriedma          #+#    #+#             */
/*   Updated: 2018/06/27 20:08:20 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_memjoin(void *a1, void *b1, size_t asize, size_t bsize)
{
	char	*n;

	n = ft_memalloc(asize + bsize + 1);
	ft_memcpy(n, a1, asize);
	ft_memcpy(&n[asize], b1, bsize);
	return ((void*)n);
}
