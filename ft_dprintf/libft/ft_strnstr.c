/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 11:07:23 by efriedma          #+#    #+#             */
/*   Updated: 2018/02/24 17:29:43 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	int		i;
	int		x;

	i = -1;
	if (!s2[0])
		return ((char*)s1);
	while (s1[++i] && i < (int)n)
	{
		x = 0;
		while (s1[i + x] == s2[x] && i + x < (int)n)
		{
			if (!s2[x + 1])
				return ((char*)s1 + i);
			x++;
		}
	}
	return (0);
}
