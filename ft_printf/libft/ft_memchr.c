/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 17:18:28 by efriedma          #+#    #+#             */
/*   Updated: 2018/02/24 17:18:36 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int i;

	i = -1;
	while (++i < (int)n)
	{
		if (((unsigned char*)s)[i] == (unsigned char)c)
			return ((void*)s + i);
	}
	return ((void*)0);
}
