/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 10:54:25 by efriedma          #+#    #+#             */
/*   Updated: 2018/02/22 18:17:27 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	z;

	z = 0;
	while (dst[z] && z < size)
		z++;
	if (size == z)
		return (size + ft_strlen(src));
	ft_strncat(&dst[z], src, size - z - 1);
	return (z + ft_strlen(src));
}
