/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encrypt-64bitblock.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 15:05:50 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/02 21:34:12 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

int			g_permute[64] = {58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17, 9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7};

unsigned long long		initial_perm(unsigned long long textblock)
{
	unsigned long long	ret;
	size_t				i;
	unsigned long long	tmp;

	i = 0;
	ret = 0;
	while (i < 64)
	{
		tmp = (pow2(g_permute[i] - 1) & textblock);
		if (((g_permute[i] + 1) > (int)i) && (g_permute[i] != (int)i))
			tmp <<= (g_permute[i] - i - 1);
		else if (g_permute[i] != (int)i)
			tmp >>= i - (g_permute[i] - 1);
		else if (g_permute[i] == (int)i)
			tmp >>= 1;
		ret += (tmp);
		i++;
	}
	return (ret);
}
