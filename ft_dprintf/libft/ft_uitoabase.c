/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoabase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 15:31:31 by efriedma          #+#    #+#             */
/*   Updated: 2018/05/25 15:31:44 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	u_set(int nbr, int cnt)
{
	if (nbr < 0 && !cnt)
	{
		cnt++;
		return ('-');
	}
	if (nbr >= 10)
		return ('a' - 10 + nbr);
	else if (nbr < 0)
		return (-nbr + '0');
	else
		return (nbr + '0');
}

int		u_numlen(unsigned long long nbr, int base)
{
	int	len;

	len = 0;
	if (!nbr)
		return (1);
	while (nbr)
	{
		nbr /= base;
		len++;
	}
	return (len);
}

char	*ft_uitoabase(unsigned long long nbr, int base)
{
	char		*str;
	int			i;
	int			x;
	static int	cnt;

	cnt = 0;
	i = 0;
	x = u_numlen(nbr, base) - 1;
	str = ft_memalloc(x + 3);
	if (!nbr)
		str[0] = '0';
	while (nbr)
	{
		str[x] = u_set(nbr % base, cnt);
		nbr /= base;
		x--;
	}
	return (str);
}
