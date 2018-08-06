/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 11:58:12 by efriedma          #+#    #+#             */
/*   Updated: 2018/03/06 22:17:39 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if (ft_strlen(s) < start)
		return (0);
	ptr = (char*)malloc(sizeof(char) * ((int)len + 1));
	if (ptr)
	{
		while (s[start + i] && i < len)
		{
			ptr[i] = s[start + i];
			i++;
		}
		ptr[i] = 0;
		return (ptr);
	}
	return (0);
}
