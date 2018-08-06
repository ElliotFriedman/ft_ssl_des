/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nwputstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 14:35:24 by efriedma          #+#    #+#             */
/*   Updated: 2018/05/25 17:16:48 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_nwputstr(wchar_t *str, t_data *curr, int i)
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
