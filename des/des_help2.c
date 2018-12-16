/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 22:36:28 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/10 03:08:47 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

extern int					g_sbox[32][16];
extern int					g_fperm[64];
extern size_t				g_passlen;
extern char					*g_tmp;
extern unsigned long long	g_key;
extern char					*g_saltchars;
extern int					g_saltcharbool;
extern int					g_b64;
extern int					g_decrypt;
extern int					g_cbc;
extern int					g_out;
extern size_t				g_strlen;
extern size_t				g_saltbool;
extern int					g_ka;
extern size_t				g_ivbool;
extern size_t				g_salt;
extern size_t				g_nosalt;
extern char					*g_pass;
extern size_t				g_fileidx;
extern int					g_permute[64];
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
extern size_t				g_x;
extern unsigned long long	g_ret;

size_t				c_num(size_t num)
{
	if (num % 8 == 0)
		return (num + 8);
	while (num % 8 != 0)
		num++;
	return (num);
}

void				create_subkeys(unsigned long long key)
{
	size_t	i;
	size_t	ltmp;
	size_t	rtmp;

	i = 0;
	g_rsubkey[0] = (size_t)((key & 0xFFFFFFF000000000ul) >> 32);
	g_lsubkey[0] = (size_t)(key & 0xFFFFFFF00) >> 4;
	while (i < 16)
	{
		if (i)
		{
			g_lsubkey[i] = g_lsubkey[i - 1];
			g_rsubkey[i] = g_rsubkey[i - 1];
		}
		ltmp = (g_rotate[i] == 1 ? 1 << 31 : 3 << 30) & g_lsubkey[i];
		rtmp = (g_rotate[i] == 1 ? 1 << 31 : 3 << 30) & g_rsubkey[i];
		g_lsubkey[i] <<= g_rotate[i];
		g_rsubkey[i] <<= g_rotate[i];
		g_lsubkey[i] += ltmp >> (g_rotate[i] == 1 ? 27 : 26);
		g_rsubkey[i] += rtmp >> (g_rotate[i] == 1 ? 27 : 26);
		i++;
	}
	concat_subkeys();
}

void				init_txtblock(unsigned long long *block,
		unsigned char *chrblock)
{
	size_t	i;

	i = 0;
	*block = 0;
	while (i < 8)
	{
		*block += chrblock[i];
		if (i + 1 != 8)
			*block <<= 8;
		i++;
	}
}

unsigned long long	sboxes(unsigned long long expandrside)
{
	unsigned long long	r;
	size_t				i;
	size_t				tmp;

	i = 0;
	tmp = 0;
	r = 0;
	while (i < 32)
	{
		tmp = (expandrside & 0xFC00000000000000ul) >> 58;
		r += g_sbox[i + (((tmp & 1) | ((tmp & 32) >> 4)) & 3)][(tmp & 30) >> 1];
		if (i + 4 != 32)
			r <<= 4;
		expandrside <<= 6;
		i += 4;
	}
	r <<= 32;
	return (r);
}

unsigned long long	final_permutate(unsigned long long rside)
{
	unsigned long long	ret;
	size_t				i;
	unsigned long long	tmp;

	i = 0;
	ret = 0;
	while (i < 64)
	{
		tmp = (pow2(g_fperm[i] - 1) & rside);
		if (((g_fperm[i] + 1) > (int)i) && (g_fperm[i] != (int)i))
			tmp <<= (g_fperm[i] - i - 1);
		else if (g_fperm[i] != (int)i)
			tmp >>= i - (g_fperm[i] - 1);
		else if (g_fperm[i] == (int)i)
			tmp >>= 1;
		ret += (tmp);
		i++;
	}
	return (ret);
}
