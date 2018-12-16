/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_help3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 03:09:13 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/10 03:13:09 by efriedma         ###   ########.fr       */
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

char	*l_bytes(unsigned long long aside)
{
	char	*ret;
	char	*cpy;

	cpy = 0;
	ret = ft_memalloc(8);
	cpy = (char *)&aside;
	ret[0] = cpy[0];
	ret[1] = cpy[1];
	ret[2] = cpy[2];
	ret[3] = cpy[3];
	ret[4] = cpy[4];
	ret[5] = cpy[5];
	ret[6] = cpy[6];
	ret[7] = cpy[7];
	return (ret);
}

void	loopinner(
		unsigned long long *rside,
		unsigned long long *lside,
		unsigned long long *aside_next)
{
	*aside_next = *rside;
	*rside = permuterightside(*rside);
	*rside = sboxes(*rside ^ g_k[g_i]);
	*rside = pperm(*rside);
	*rside = *lside ^ *rside;
	*lside = *aside_next;
	g_i++;
}

void	initvar(
		unsigned long long *textblock,
		unsigned long long *lside,
		unsigned long long *rside,
		unsigned long long *key)
{
	*textblock = initial_perm(*textblock);
	*lside = *textblock >> 32;
	*lside <<= 32;
	*rside = (0xFFFFFFFF & *textblock) << 32;
	*key = initialperm(*key);
	g_i = 0;
	if (!g_cbc && !g_decrypt)
		g_ciphertext = 0;
}

char	*encrypted_des(char *data, unsigned long long key)
{
	unsigned long long	lside;
	unsigned long long	rside;
	unsigned long long	aside_next;
	unsigned long long	textblock;

	init_txtblock(&textblock, (unsigned char*)data);
	if (g_cbc && !g_decrypt)
		textblock ^= g_iv;
	else if (g_cbc && g_decrypt)
		g_ciphertext = textblock;
	initvar(&textblock, &lside, &rside, &key);
	while (g_i < 16)
		loopinner(&rside, &lside, &aside_next);
	if (g_cbc && !g_decrypt)
		g_iv = final_permutate(rside | (lside >> 32));
	else if (g_cbc && g_decrypt)
	{
		g_ret = final_permutate(rside | (lside >> 32));
		g_ret ^= g_iv;
		g_iv = g_ciphertext;
		return (l_bytes(g_ret));
	}
	return (l_bytes(((final_permutate(rside | (lside >> 32))))));
}
