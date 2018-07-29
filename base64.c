/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 13:29:03 by efriedma          #+#    #+#             */
/*   Updated: 2018/07/28 21:18:09 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

const char	g_ref[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
int			g_pad;

int	findb_len(int len)
{
	int	t_bits;

	t_bits = len * 8;
	while (t_bits % 6 != 0)
		t_bits++;
	return (t_bits / 6);
}

unsigned char	*base64_encode(unsigned char *str, int len)
{
	int		nlen;
	int		bit_len;
	int		m;
	size_t	i;
	unsigned char	*n;
	
	g_pad = ((len * 8) % 3);
	
	bit_len = findb_len(len);
	n = ft_memalloc(bit_len + 1);
	i = 0;
	m = 0;
	ft_printf("bit_len %d\n", bit_len);
	while (i < bit_len)
	{
		n[i] = g_ref[(str[m] & 252) >> 2];
		n[i + 1] = g_ref[(  ((str[m] & 3) << 4) |  ((str[m + 1] & 240) >> 4))];
		n[i + 2] = g_ref[(  ((str[m + 1] & 15) << 2)   |   (((str[m + 2] & 192) >> 6))   )];
		n[i + 3] = g_ref[(     str[m + 2] & 63  )];
		m += 3;
		i += 4;
	}
	ft_printf("n before padding %s\n", n);
	i -= g_pad;
	while (g_pad)
	{
		ft_printf("appending =\n");
		n[i] = '=';
		i++;
		g_pad--;
	}
	return (n);
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		unsigned char *n = base64_encode((unsigned char *)argv[1], ft_strlen((char*)argv[1]));
		ft_printf("%s\n", n);
		free(n);
	}
	return (0);
}
