/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 13:29:03 by efriedma          #+#    #+#             */
/*   Updated: 2018/09/09 19:56:11 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"
int			g_len;

int				find_chr(char c)
{
	size_t		i;

	i = 0;
	while (i < 64)
	{
		if (g_ref[i] == c)
			return (i);
		i++;
	}
	return (0);
}

unsigned char	*base64_decode(unsigned char *str, int len)
{
	int				x;
	size_t			i;
	unsigned char	*n;
	unsigned int	tmp;

	i = 0;
	x = 0;
	tmp = 0;
	n = ft_memalloc(((len / 4) * 3) + 3);
	//convert from char to corresponding index in b64
	while ((int)i < len)
	{
		str[i] = find_chr(str[i]);
		i++;
	}
	i = 0;
	//put 4 char values into a unsigned int
	//then transfer the values from the uint
	//into the new string
	while ((int)i < len)
	{
		tmp = (str[i] << 2);
		tmp <<= 6;
		tmp += (str[i + 1] << 2);
		tmp <<= 6;
		tmp += (str[i + 2] << 2);
		tmp <<= 6;
		tmp += (str[i + 3] << 2);
		tmp <<= 6;

		n[x] = (tmp >> 24) & 255;
		n[x + 1] = (tmp >> 16) & 255;
		n[x + 2] = (tmp >> 8) & 255;
		tmp = 0;
		i += 4;
		x += 3;
	}
	//return the newly created string :)
	g_len = x;
	return (n);
}
