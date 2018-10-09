/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des-encrypt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 18:20:16 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/08 23:51:18 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

# define LROT(x, rotate) (x << rotate) | (x >> (32 - rotate))
int							g_fperm[64] = {40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41, 9, 49, 17, 57, 25};
int							g_sbox[32][16] = {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
	{0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
	{4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
	{15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
	{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
	{3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
	{0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
	{13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
	{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
	{13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
	{13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
	{1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
	{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
	{13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
	{10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
	{3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
	{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
	{14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
	{4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
	{11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
	{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
	{10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
	{9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
	{4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
	{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
	{13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
	{1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
	{6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
	{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
	{1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
	{7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
	{2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}};
int							g_permute[64];
int							g_nopad;
extern unsigned int			g_decrypt;
extern int					g_cbc;
int							g_cpermutation[48] = {14, 17, 11, 24, 1, 5,
	3,  28, 15, 6, 21, 10,
	23, 19, 12, 4, 26, 8,
	16, 7, 27, 20, 13, 2,
	41,  52, 31, 37, 47, 55,
	30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53,
	46, 42, 50, 36, 29, 32};
int							g_expandpermutation[48] = {32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9,
	8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};
int							g_rotate[16] = {1, 1, 2, 2,
	2, 2, 2, 2,
	1, 2, 2, 2,
	2, 2, 2, 1};
unsigned long long			g_arr[16];
unsigned int				g_rsubkey[16];
unsigned int				g_lsubkey[16];
unsigned long long			g_concatsubkeys[16];
extern unsigned long long	g_iv;
unsigned int				g_len;
unsigned long long			g_k[16];
unsigned long long			lmax = 0xFFFFFFFFFFFFFFFF;
size_t				g_i;
unsigned long long	g_ciphertext;

size_t						c_num(size_t num)
{
	if (num % 8 == 0)
		return (num + 8);
	while (num % 8 != 0)
		num++;
	return (num);
}

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
		if (((g_expandpermutation[i] + 1) > (int)i) && (g_expandpermutation[i] != (int)i))
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
	size_t	i;
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

void	create_subkeys(unsigned long long key)
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
		ltmp = (g_rotate[i] == 1 ? 1 << 31: 3 << 30) & g_lsubkey[i];
		rtmp = (g_rotate[i] == 1 ? 1 << 31: 3 << 30) & g_rsubkey[i];
		g_lsubkey[i] <<= g_rotate[i];
		g_rsubkey[i] <<= g_rotate[i];
		g_lsubkey[i] += ltmp >> (g_rotate[i] == 1 ? 27 : 26);
		g_rsubkey[i] += rtmp >> (g_rotate[i] == 1 ? 27 : 26);
		i++;
	}
	concat_subkeys();
}

void	init_txtblock(unsigned long long *block, unsigned char *chrblock)
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
	unsigned long long	ret;
	size_t				i;
	size_t				tmp;

	i = 0;
	tmp = 0;
	ret = 0;
	while (i < 32)
	{
		tmp = (expandrside & 0xFC00000000000000ul) >> 58;
		ret += g_sbox[i + (((tmp & 1) | ((tmp & 32) >> 4)) & 3)] [(tmp & 30) >> 1];
		if (i + 4 != 32)
			ret <<= 4;
		expandrside <<= 6;
		i += 4;
	}
	ret <<= 32;
	return (ret);
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

void	pbyte(char *str, size_t len);

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
		unsigned long long ret = final_permutate(rside | (lside >> 32));
		ret ^= g_iv;
		g_iv = g_ciphertext;
		return (l_bytes(ret));
	}
	return l_bytes(((final_permutate(rside | (lside >> 32)))));
}

void				swaplong_endian(char *encrypt)
{
	char	b[8];
	b[0] = encrypt[0];
	b[1] = encrypt[1];
	b[2] = encrypt[2];
	b[3] = encrypt[3];
	b[4] = encrypt[4];
	b[5] = encrypt[5];
	b[6] = encrypt[6];
	b[7] = encrypt[7];

	encrypt[0] = b[7];
	encrypt[1] = b[6];
	encrypt[2] = b[5];
	encrypt[3] = b[4];
	encrypt[4] = b[3];
	encrypt[5] = b[2];
	encrypt[6] = b[1];
	encrypt[7] = b[0];
}

void			swap_long_endian(char *encrypt, size_t bytes)
{
	size_t			i;

	i = 0;
	while (i < (bytes / 8))
	{
		swaplong_endian(&encrypt[i]);
		i++;
	}
}

void        print_bytes(unsigned long long *data, int len);

void	print_spec(char *str, size_t bytes)
{
	size_t i = 0;

	while (i < bytes)
	{
		ft_printf("%c", str[i]);
		i++;
	}
	ft_putstr("\n");
}

unsigned long long	char2long(unsigned long long *block, unsigned char *chrblock)
{
	size_t	i;

	i = 0;
	*block = 0;
	while (i < 8)
	{
		*block <<= 8;
		*block += chrblock[i];
		i++;
	}
	return (*block);
}

void				helpencrypt(char **encrypt, size_t *len)
{
	encrypt[0] = des_pad(encrypt[0], *len);
	*len = c_num(*len);
	g_len = *len;
}

unsigned long long	*des_encrypt(unsigned long long key, char *encrypt, size_t len)
{
	//all of these get freed
	char				*print;
	char				*tmp;
	char				*tmp2;
	//free deez
	
	unsigned long long	stor[c_num(len) + 1];
	size_t	i;

	i = 0;
	print = ft_memalloc(len);
	key = init_subkey(key);
	if (!g_decrypt)
		helpencrypt(&encrypt, &len);
	create_subkeys(key);
	while (i < len)
	{
		tmp = print;
		tmp2 = (char*)encrypted_des(&encrypt[i], key);	
		print = ft_memjoin(print, tmp2, i, 8);
		
		ft_memdel((void**)&tmp);
		ft_memdel((void**)&tmp2);
		
		unsigned long long t = char2long(&key, (unsigned char*)&print[i]);
		stor[i / 8] = t;
		i += 8;
	}
	free(print);
	g_len = len;
	free(encrypt);
	//return this
	return (ft_memdup(stor, len));
}
