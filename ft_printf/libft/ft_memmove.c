/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 22:17:14 by efriedma          #+#    #+#             */
/*   Updated: 2018/02/24 17:13:10 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = -1;
	if (s1 < s2)
	{
		while (++i < n)
			((unsigned char*)s1)[i] = ((unsigned char*)s2)[i];
	}
	else
		while (n--)
			((unsigned char*)s1)[n] = ((unsigned char*)s2)[n];
	return (s1);
}
