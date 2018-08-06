/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 17:23:21 by efriedma          #+#    #+#             */
/*   Updated: 2018/02/24 17:23:45 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*cpy;
	int		a;
	int		i;

	a = (int)ft_strlen(str);
	cpy = (char*)malloc(sizeof(char) * a + 1);
	i = -1;
	if (cpy)
	{
		while (++i < a)
			cpy[i] = str[i];
		cpy[i] = '\0';
	}
	return (cpy);
}
