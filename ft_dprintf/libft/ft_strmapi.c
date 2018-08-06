/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 11:56:24 by efriedma          #+#    #+#             */
/*   Updated: 2018/02/24 16:53:37 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*ptr;

	if (s && f)
	{
		i = -1;
		ptr = (char*)malloc(sizeof(char) * (int)ft_strlen(s) + 1);
		if (ptr)
		{
			while (s[++i])
				ptr[i] = f(i, s[i]);
			ptr[i] = '\0';
		}
		return (ptr);
	}
	return (0);
}
