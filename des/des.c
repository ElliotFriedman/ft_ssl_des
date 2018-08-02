/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 16:06:46 by efriedma          #+#    #+#             */
/*   Updated: 2018/08/02 15:22:27 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

int			g_grab[56] = {57, 49, 41, 33, 25, 17, 9,
						1, 58, 50, 42, 34, 26, 18,
						10, 2, 59, 51, 43, 35, 27,
						19, 11, 3, 60, 52, 44, 36,
						63, 55, 47, 39, 31, 23, 15,
						7, 62, 54, 46, 38, 30, 22,
						14, 6, 61, 53, 45, 37, 29,
						21, 13, 5, 28, 20, 12, 4};

int			_rand0(FILE *e)
{
	unsigned int	a;

	a = (unsigned int)getc(e);
	while ((a & 127) < 32)
		a += (unsigned int)getc(e);
	return ((int)a);
}

void		create_salt_8bytes(char *salt, FILE *e)
{
	int		i;

	i = 0;
	while (i < 8)
	{
		salt[i] = (char)_rand0(e) & 127;
		i++;
	}
	salt[8] = 0;
}

void		swap_4bytes(int *data)
{
	int	a;

	a = data[0];

	data[0] = data[1];
	data[1] = a;
}

void		pint_bytes(void *data, int len)
{
	size_t	i = 0;
	unsigned char	*print;

	print = (char *)data;
	swap_4bytes((int*)data);
	while (i < len)
	{
		ft_printf("%02X", print[i]);
		i++;
	}
	ft_putstr("\n");
}


uint64_t		subkey(unsigned long long key)
{
	uint64_t	ret;
	size_t		i;
	size_t		tmp;

	ret = 0;
	i = 0;
	while (i < 56)
	{
		tmp = key >> g_grab[i];
		ret |= tmp;
		ret <<= 1;
		i++;
	}
	return (ret);
}

void		des(char **argv, int argc)
{
	unsigned long long	*tmp;
	unsigned long long	*key;
	char 				*pass;
	char				salt[9];
	int					i = 0;
	FILE            	*e;

	pass = getpass("Enter your password:");
	e = fopen("/dev/urandom", "r");
	create_salt_8bytes(salt, e);
	ft_printf("Random salt: %s\n", salt);
	fclose(e);
	ft_printf("Salt: %02X%02X%02X%02X%02X%02X%02X%02X\n", salt[0], salt[1], salt[2], salt[3], salt[4], salt[5],salt[6], salt[7]);
	tmp = create_key(pass);
	key = tmp;
	ft_putstr("key = ");
	print_bytes((void*)tmp, 8);
	ft_printf("key in binary: %064b\n", key);
	tmp++;
	ft_putstr("iv =");
	print_bytes((void*)tmp, 8);
	//do subkey after byte order has been changed to big endian
}
