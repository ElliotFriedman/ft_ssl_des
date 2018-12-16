/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_permute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 02:45:43 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/10 02:51:00 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

extern int					g_fperm[64];
extern int					g_sbox[32][16];
extern int					g_permute[64];
extern int					g_nopad;
extern unsigned int			g_decrypt;
extern int					g_cbc;
extern int					g_cpermutation[48];
extern int					g_expandpermutation[48];
extern int					g_rotate[16];
extern unsigned long long	g_arr[16];
extern unsigned int			g_rsubkey[16];
extern unsigned int			g_lsubkey[16];
extern unsigned long long	g_concatsubkeys[16];
extern unsigned long long	g_iv;
extern unsigned int			g_len;
extern unsigned long long	g_k[16];
extern size_t				g_i;
extern unsigned long long	g_ciphertext;

unsigned long long	permuterightside(unsigned long long rside)
{
	unsigned long long	ret;
	size_t				i;
	unsigned long long	tmp;

	i = 0;
	ret = 0;
	while (i < 48)
	{
		tmp = (pow2(g_expandpermutation[i] - 1) & rside);
		if (((g_expandpermutation[i] + 1) > (int)i)
				&& (g_expandpermutation[i] != (int)i))
			tmp <<= (g_expandpermutation[i] - i - 1);
		else if (g_expandpermutation[i] != (int)i)
			tmp >>= i - (g_expandpermutation[i] - 1);
		else if (g_expandpermutation[i] == (int)i)
			tmp >>= 1;
		ret += (tmp);
		i++;
	}
	return (ret);
}

unsigned long long	initialperm(unsigned long long txt)
{
	size_t				i;
	unsigned long long	ret;

	i = 0;
	ret = 0;
	while (i < 64)
	{
		ret += ((txt >> (g_permute[i] - 1)) & 1) << i;
		i++;
	}
	return (ret);
}

unsigned long long	permute_concatsubkeys(size_t x)
{
	unsigned long long	ret;
	size_t				i;
	unsigned long long	tmp;

	i = 0;
	ret = 0;
	while (i < 48)
	{
		tmp = (pow2(g_cpermutation[i] - 1) & g_arr[x]);
		if (((g_cpermutation[i] + 1) > (int)i) && (g_cpermutation[i] != (int)i))
			tmp <<= (g_cpermutation[i] - i - 1);
		else if (g_cpermutation[i] != (int)i)
			tmp >>= i - (g_cpermutation[i] - 1);
		else if (g_cpermutation[i] == (int)i)
			tmp >>= 1;
		ret += (tmp);
		i++;
	}
	return (ret);
}

void				concat_subkeys(void)
{
	size_t				i;

	i = 0;
	while (i < 16)
	{
		g_arr[i] = g_rsubkey[i];
		g_arr[i] <<= 28;
		g_arr[i] += (g_lsubkey[i]);
		g_arr[i] <<= 4;
		i++;
	}
	i = -1;
	if (!g_decrypt)
		while (++i < 16)
			g_k[i] = permute_concatsubkeys(i);
	else
		while (++i < 16)
			g_k[i] = permute_concatsubkeys(15 - i);
}

unsigned long long	comp_perm(unsigned long long i56bit)
{
	unsigned long long	i48bit;
	size_t				i;

	i = 0;
	i48bit = 0;
	i56bit >>= 8;
	while (i < 8)
	{
		i48bit |= (g_cpermutation[i] >> i56bit) & 1;
		i++;
	}
	return (i48bit);
}
