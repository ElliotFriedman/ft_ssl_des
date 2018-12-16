/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 11:31:46 by efriedma          #+#    #+#             */
/*   Updated: 2018/03/04 14:27:57 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_clr_whitespace(const char *str)
{
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
			|| *str == '\r' || *str == '\f')
		str++;
	return ((char*)str);
}

int			ft_atoi(const char *str)
{
	int					isneg;
	int long long		nbr;

	nbr = 0;
	isneg = 0;
	str = ft_clr_whitespace(str);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			isneg++;
		str++;
	}
	while (ft_isdigit((int)*str))
	{
		nbr *= 10;
		nbr += *str - 48;
		str++;
	}
	if (isneg)
		return (-nbr);
	return (nbr);
}
