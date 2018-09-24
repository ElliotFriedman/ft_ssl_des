/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_removewhitespace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 23:35:01 by efriedma          #+#    #+#             */
/*   Updated: 2018/09/23 22:17:06 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	removewhitespace(char *str)
{
	size_t	i;
	size_t	x;

	i = 0;
	x = i;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
		{
			x = i;
			i = 0;
			while (str[x])
			{
				str[x] = str[x + 1]; 
				x++;
			}
		}
		i++;
	}
}
