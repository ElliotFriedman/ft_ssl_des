/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mputstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 18:10:16 by efriedma          #+#    #+#             */
/*   Updated: 2018/09/16 23:29:16 by efriedma         ###   ########.fr       */
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
		i = ft_strlen(str);
		curr->iter += i;
		write(1, str, i);
	}
}
