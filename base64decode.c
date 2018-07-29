/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 13:29:03 by efriedma          #+#    #+#             */
/*   Updated: 2018/07/09 13:58:29 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

				   //0123456789012345678901234567890123456789012345678901234567890123
char    g_ref[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int	findb_len(int len)
{
	int	t_bits;

	t_bits = len * 6;
	while (t_bits % 8 != 0)
		t_bits--;
	return (t_bits / 8);
}

unsigned char	*base64_decode(unsigned char *str, int len)
{
	int		nlen;
	int		bit_len;
	int		m;
	size_t	i;
	size_t	b00l;
	unsigned char	*n;

	/*
	 *
	 *		Make a boolean to see if we need = sign or not
	 *	this is very important for padding if we need it
	 *	
	 *	make a base 64 decode too
	 *
	 *	add ciper error messages and b64, add these as functions :)
	 *
	 */
	b00l = (len * 8) % 6;
	bit_len = findb_len(len);
	n = ft_memalloc(bit_len);
	i = 0;
	m = 0;
	while (i < bit_len)
	{
		//int z = magico(&m, str);
		//1			
		//		    \/	   \/
		//			0000  0000 | 0000  0000 | 0000 0000 
			n[i] = g_ref[(str[m] & 252) >> 2];//magico(m, str)];
		//2				   \/	     \/ 	  
		//			0000  0000 | 0000  0000 | 0000 0000 
			n[i + 1] = g_ref[(  ((str[m] & 3) << 4) |  ((str[m + 1] & 240) >> 4))];
		//3
		//							 \/		   \/
		//			0000  0000 | 0000  0000 | 0000 0000
		//						   11  1111
			n[i + 2] = g_ref[(  ((str[m + 1] & 15) << 2)   |   (((str[m + 2] & 192) >> 6))   )];
		//4
		//									   \/	  \/
		//			0000  0000 | 0000  0000 | 0000 0000
			n[i + 3] = g_ref[(     str[m + 2] & 63  )];
		//ft_printf("m: %d, i: %d\n", m, i);
		m += 3;
		i += 4;
	}
	while (b00l)
	{
		i -= 1;
		n[i] = '=';
		i++;
		b00l--;
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
