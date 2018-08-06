/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoabase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 15:30:52 by efriedma          #+#    #+#             */
/*   Updated: 2018/05/25 15:31:03 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	set(int nbr)
{
	if (nbr >= 10)
		return ('a' - 10 + nbr);
	else if (nbr < 0)
		return (-nbr + '0');
	else
		return (nbr + '0');
}

int		numlen(long long nbr, int base)
{
	int	len;

	len = 0;
	if (!nbr)
		return (2);
	while (nbr)
	{
		nbr /= base;
		len++;
	}
	return (len);
}

char	*ft_itoabase(long long nbr, int base)
{
	char		*str;
	long long	stand;
	int			x;

	x = numlen(nbr, base) - 1;
	str = ft_memalloc(x + 2);
	if (!nbr)
		str[0] = '0';
	stand = nbr;
	if (nbr < 0)
		stand = nbr * -1;
	while (stand)
	{
		str[x] = set(stand % base);
		stand /= base;
		x--;
	}
	return (str);
}
