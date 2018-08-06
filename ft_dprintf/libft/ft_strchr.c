/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 16:50:26 by efriedma          #+#    #+#             */
/*   Updated: 2018/02/24 16:50:28 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	if ((char)c == '\0' && !s[0])
		return ((char*)s + i);
	while (s[i])
	{
		if ((char)c == s[i])
			return ((char*)s + i);
		i++;
		if ((char)c == s[i])
			return ((char*)s + i);
	}
	return ((char*)0);
}
