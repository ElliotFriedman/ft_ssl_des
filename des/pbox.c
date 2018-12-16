/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbox.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 14:50:34 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/09 22:52:14 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

int	g_pperm[32] = {16, 7, 20, 21, 29, 12, 28, 17,
	1, 15, 23, 26, 5, 18, 31, 10,
	2, 8, 24, 14, 32, 27, 3, 9,
	19, 13, 30, 6, 22, 11, 4, 25};

int	g_grab[56] = {57, 49, 41, 33, 25, 17, 9,
	1, 58, 50, 42, 34, 26, 18,
	10, 2, 59, 51, 43, 35, 27,
	19, 11, 3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	7, 62, 54, 46, 38, 30, 22,
	14, 6, 61, 53, 45, 37, 29,
	21, 13, 5, 28, 20, 12, 4};

unsigned long long			pperm(unsigned long long txtblock)
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
	return (ret);
}

unsigned long long			pow2(size_t amt)
{
	unsigned long long int	ret;

	ret = 9223372036854775808ul;
	while (amt--)
		ret >>= 1;
	return (ret);
}

unsigned long long			init_subkey(unsigned long long key)
{
	unsigned long long	ret;
	size_t				i;
	unsigned long long	tmp;

	i = 0;
	ret = 0;
	while (i < 56)
	{
		tmp = 0;
		tmp = (pow2(g_grab[i] - 1) & key);
		if ((g_grab[i] + 1) > (int)i)
			tmp <<= (g_grab[i] - i - 1);
		else
			tmp >>= i - (g_grab[i] - 1);
		ret += (tmp);
		i++;
	}
	return (ret);
}

unsigned long long			sub_block(unsigned long long key)
{
	unsigned long long		ret;
	size_t					i;
	size_t					tmp;

	i = 0;
	ret = 0;
	while (i < 56)
	{
		tmp = key << g_grab[i];
		ret |= tmp;
		ret <<= 1;
		i++;
	}
	return (ret);
}
