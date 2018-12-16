/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 10:23:18 by efriedma          #+#    #+#             */
/*   Updated: 2018/05/22 17:40:15 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_clr_whitespace(const char *str)
{
	int x;

	x = find_len(str);
	while ((!ft_isdigit(*str) || *str == '0')
			&& *str != '.' && *str != '\n' && *str && x)
	{
		x--;
		str++;
	}
	return ((char *)str);
}

int			ft_matoi(const char *str)
{
	int					i;
	int					isneg;
	int long long		nbr;

	i = 0;
	nbr = 0;
	isneg = 0;
	str = ft_clr_whitespace(str);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			isneg++;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		nbr *= 10;
		nbr += str[i] - 48;
		i++;
	}
	if (isneg)
		return (-nbr);
	return (nbr);
}
