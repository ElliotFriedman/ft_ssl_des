/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 11:51:17 by efriedma          #+#    #+#             */
/*   Updated: 2018/02/24 17:28:56 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f) (char))
{
	int		i;
	char	*ptr;

	if (s && f)
	{
		i = -1;
		ptr = (char*)malloc(sizeof(char) * ft_strlen(s) + 1);
		if (ptr)
		{
			while (s[++i])
				ptr[i] = f(s[i]);
			ptr[i] = '\0';
			return (ptr);
		}
	}
	return (0);
}
