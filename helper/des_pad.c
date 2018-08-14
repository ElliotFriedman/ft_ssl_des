/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_pad.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 18:02:38 by efriedma          #+#    #+#             */
/*   Updated: 2018/08/13 19:29:17 by efriedma         ###   ########.fr       */
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
	data[7] = n.a;
	data[6] = n.b;
	data[5] = n.c;
	data[4] = n.d;
	data[3] = n.e;
	data[2] = n.f;
	data[1] = n.g;
	data[0] = n.h;
}


void		rev_8byte(char *data, size_t len)
{
	size_t	i;

	i = 0;
	if (len % 8 != 0)
	{
		//panic function.
		//This condition should NEVER trigger
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

	//this will be freed after we re assign data
	tmp = data;
	bytes++;
	//add an extra byte
	snew = ft_memalloc(bytes);
	//copy the old bytes in from data
	ft_memcpy(snew, data, bytes - 1);
	//free the old data
	free(tmp);
	//return the new data
	return (snew);
}

char	*des_pad(char *encrypt, size_t len)
{
	size_t	dif;
	char	set[1];

	dif = len % 8;
//	ft_printf("dif: %d\n", dif);
	set[0] = 8 - dif;
	if (dif == 0)
		set[0] = 8;
	dif = set[0];
//	ft_printf("adding %d bytes\n", dif);
	while (dif)
	{
//		ft_printf("Dif in while loop %d, Len: %d\n", dif, len + 1);
		len++;
		encrypt = _add_byte(encrypt, len);
		ft_memset(&encrypt[len - 1], (int)set[0], 1);
//		print_bytes(encrypt, len);
		dif--;
	}
	ft_printf("total len %d\n", len);
	return (encrypt);
}

/*
int main(void)
{
	char *a = ft_memalloc(12);
	ft_strcpy(a, "Pad me12 b1");
	print_bytes(a, ft_strlen(a));
	a = des_pad(a, ft_strlen(a));
	print_bytes(a, 16);
	return 1;
}
*/
