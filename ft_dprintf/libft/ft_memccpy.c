/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 17:18:02 by efriedma          #+#    #+#             */
/*   Updated: 2018/02/24 17:18:22 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	int i;

	i = -1;
	if ((int)n < 0)
		n = ft_strlen(s2);
	while (++i < (int)n)
	{
		((unsigned char *)s1)[i] = ((unsigned char *)s2)[i];
		if (((unsigned char*)s1)[i] == (unsigned char)c)
			return (s1 + i + 1);
	}
	return (0);
}
