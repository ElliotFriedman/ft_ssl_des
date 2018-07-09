/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 11:00:13 by efriedma          #+#    #+#             */
/*   Updated: 2018/02/24 17:14:38 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int		i;
	int		x;

	if (!s2[0])
		return ((char*)s1);
	i = -1;
	while (s1[++i])
	{
		x = 0;
		while (s1[i + x] == s2[x])
		{
			if (!s2[x + 1])
				return ((char*)&s1[i]);
			x++;
		}
	}
	return (NULL);
}
