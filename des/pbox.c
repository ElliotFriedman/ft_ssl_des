/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbox.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 14:50:34 by efriedma          #+#    #+#             */
/*   Updated: 2018/09/09 18:16:25 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

int	g_pperm[32] = {16,	7,	20,	21,	29,	12,	28,	17,
	1,	15,	23,	26,	5,	18,	31,	10,
	2,	8,	24,	14,	32,	27,	3,	9,
	19,	13,	30,	6,	22,	11,	4,	25};


unsigned long long		pperm(unsigned long long txtblock)
{
	unsigned long long	ret;
	unsigned long long	tmp;
	size_t				i;

	i = 0;
	ret = 0;
	while (i < 32)
	{
		tmp = (pow2(g_pperm[i] - 1) & txtblock);
		if (((g_pperm[i] + 1) > (int)i) && (g_pperm[i] != (int)i))
			tmp <<= (g_pperm[i] - i - 1);
		else if (g_pperm[i] != (int)i)
			tmp >>= i - (g_pperm[i] - 1);
		else if (g_pperm[i] == (int)i)
			tmp >>= 1;
		ret += (tmp);
		i++;
	}
//	ft_printf("\n\nOutput of pperm: %064b\n\n", ret);
	return (ret);
}
