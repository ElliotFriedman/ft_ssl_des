/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mputstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 18:10:16 by efriedma          #+#    #+#             */
/*   Updated: 2018/05/23 14:23:37 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_nputstr(char *str, t_data *curr, int i)
{
	int	x;

	x = 0;
	while (str[x] && x < i)
	{
		write(1, &str[x], 1);
		curr->iter++;
		x++;
	}
}

void	ft_mputstr(char *str, t_data *curr)
{
	size_t	i;

	i = 0;
	if (str)
	{
		i = 0;
		while (str[i])
		{
			curr->iter++;
			write(1, &str[i], 1);
			i++;
		}
	}
}
