/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 13:29:03 by efriedma          #+#    #+#             */
/*   Updated: 2018/07/28 22:57:30 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

const char	g_ref[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
int			g_idx[127];
int			g_pad;

int	findb_len(int len)
{
	int	t_bits;

	t_bits = len * 8;
	while (t_bits % 6 != 0)
		t_bits++;
	return (t_bits / 6);
}

void			init_idx(void)
{
	size_t		i;
	char		a;

	i = -1;
	a = 'A';
	while (++i < 26 && a++)
	{
		g_idx[a] = i;
	}
	a = 'a';
	while (++i < 52 && a++)
	{
		g_idx[a] = i;
	}
	a = '0'
	while (++i < 62 && a++)
	{
		g_idx[a] = i;
	}
	g_idx['+'] = i++;
	g_idx['/'] = i++;
	//g_idx['='] does not need to be set equal to 0 because globals are zeroed by default

}

//here we are going from 4 bytes to 3 bytes.
//
//Relationship between these bytes
//
//len * 3 / 4 

unsigned char	*base64_decode(unsigned char *str, int len)
{
	int		bit_len;
	int		m;
	size_t	i;
	unsigned char	*n;

	init_idx();
	g_pad = ((len * 8) % 3);
	bit_len = len * 3 / 4;
	n = ft_memalloc(bit_len + 1);
	i = 0;
	m = 0;
	//ft_printf("bit_len %d\n", bit_len);
	while ((int)i < bit_len)
	{
		n[i] = g_ref[(str[m] & 252) >> 2];
		n[i + 1] = g_ref[(  ((str[m] & 3) << 4) |  ((str[m + 1] & 240) >> 4))];
		n[i + 2] = g_ref[(  ((str[m + 1] & 15) << 2)   |   (((str[m + 2] & 192) >> 6))   )];
		n[i + 3] = g_ref[(     str[m + 2] & 63  )];
		m += 3;
		i += 4;
	}
	//ft_printf("n before padding %s\n", n);
	i -= g_pad;
	while (g_pad)
	{
		//ft_printf("appending =\n");
		n[i] = '=';
		i++;
		g_pad--;
	}
	return (n);
}
