/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mputstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 18:10:16 by efriedma          #+#    #+#             */
/*   Updated: 2018/05/25 17:10:51 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_nputstr(char *str, t_data *curr, int i)
{
	int	x;

	x = 0;
	while (str[x] && x < i)
	{
		write(curr->fd, &str[x], 1);
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
			write(curr->fd, &str[i], 1);
			i++;
		}
	}
}
