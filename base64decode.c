/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 13:29:03 by efriedma          #+#    #+#             */
/*   Updated: 2018/07/29 23:30:14 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

const char	g_ref[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
int			g_idx[127];
int			g_pad;

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
	int		m;
	size_t	i;
	unsigned char	*n;

	init_idx();
	n = ft_memalloc(bit_len + 1);
	i = 0;
	m = 0;
	//ft_printf("bit_len %d\n", bit_len);
	while ((int)i < len)
	{
		//turn all characters into their corresponding number
		str[i] = g_idx[str[i]];
		i++;
	}
	//
	//	Currently in memory:
	//							110000 [00] | 001011 00 | 110000 00 | 001011 00
	//
	//							1100 0000 | 1011 00 | 110000 00 | 001011 00
	//	What we want in memory:
	//							1100 0000 | 1011 1100 | 0000 1011
	//
	//	Need to turn every 4 characters into three characters
	//
	while ((int)i < len)
	{
		//
		//turn 		1001 11[00] | 1101 0100
		//
		//into		1001 1111 | 0101 0000
		//
		//first     1001 1111
		str[i] = RN(str[i + 1], 6) | str[i];

		//then chop last two bits off the second value
		//
		//second val	0101 0000
		//
		str[i + 1] = LN(str[i + 1], 2);

		//
		//
		//
		str[i + 1] = RN(str[i + 2], 4) | str[i + 1];
		

		str[i + 2] = RN(str[i + 3], 6) | str[i + 2];
		str[i + 2] = LN(str[i + 2], ) | str[i + 2];

		str[i + 3] = 0;
		//4 is the minimum length
		i += 4;
	}

	return (n);
}
