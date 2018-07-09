/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 13:29:39 by efriedma          #+#    #+#             */
/*   Updated: 2018/03/06 21:42:03 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*ptr;

	i = -1;
	if (!s1 && s2)
		return ((char*)s2);
	if (s1 && !s2)
		return ((char*)s1);
	if (!s1 && !s2)
		return (0);
	ptr = (char*)malloc(sizeof(char) * (1 + ft_strlen(s1) + ft_strlen(s2)));
	if (ptr == 0)
		return (0);
	ft_strcpy(ptr, s1);
	ft_strcat(ptr, s2);
	return (ptr);
}
