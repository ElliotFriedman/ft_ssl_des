/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_capitalize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 14:29:30 by efriedma          #+#    #+#             */
/*   Updated: 2018/03/07 14:40:01 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_capitalize(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
					|| str[i] == '\r' || str[i] == '\f' || str[i] == '\v'))
			i++;
		while (str[i] && str[i] >= 'a' && str[i] <= 'z')
		{
			str[i] = str[i] + 32;
			i++;
		}
		i++;
	}
	return (str);
}
