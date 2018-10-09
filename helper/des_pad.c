/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_pad.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 18:02:38 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/08 22:31:47 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

//void    print_bytes(char *str, int len);

//rev endianness of bytes, 8 bytes at a time
void		rev8(char *data)
{
	t_sha	n;

	n.a = data[0];
	n.b = data[1];
	n.c = data[2];
	n.d = data[3];
	n.e = data[4];
	n.f = data[5];
	n.g = data[6];
	n.h = data[7];
	data[7] = (char)n.a;
	data[6] = (char)n.b;
	data[5] = (char)n.c;
	data[4] = (char)n.d;
	data[3] = (char)n.e;
	data[2] = (char)n.f;
	data[1] = (char)n.g;
	data[0] = (char)n.h;
}


void		rev_8byte(char *data, size_t len)
{
	size_t	i;

	i = 0;
	if (len % 8 != 0)
	{
		ft_printf("Incorrect byte amount\n");
		exit(0);
	}
	while (i < len)
	{	
		rev8(&data[i]);
		i += 8;
	}
}

char		*_add_byte(char *data, size_t bytes)
{
	char	*snew;
	char	*tmp;

	tmp = data;
	snew = ft_memalloc(bytes);
	ft_memcpy(snew, data, bytes - 1);
	free(tmp);
	return (snew);
}

char	*des_pad(char *encrypt, size_t len)
{
	size_t	dif;
	char	set[1];

	dif = len % 8;
	set[0] = 8 - dif;
	if (dif == 0)
		set[0] = 8;
	dif = set[0];
	while (dif)
	{
		len++;
		encrypt = _add_byte(encrypt, len);
		ft_memset(&encrypt[len - 1], ((char)set[0] & 15), 1);
		dif--;
	}
	return (encrypt);
}
