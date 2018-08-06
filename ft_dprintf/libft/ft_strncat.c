/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 12:57:42 by efriedma          #+#    #+#             */
/*   Updated: 2018/02/24 17:34:05 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t		i;
	size_t		x;

	i = ft_strlen(dest);
	x = -1;
	while (src[++x] && n)
	{
		dest[i] = src[x];
		i++;
		n--;
	}
	dest[i] = '\0';
	return (dest);
}
