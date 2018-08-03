/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 16:06:46 by efriedma          #+#    #+#             */
/*   Updated: 2018/08/02 21:47:16 by efriedma         ###   ########.fr       */
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

int			g_rotate[16] = {1, 1, 2, 2,
							2, 2, 2, 2,
							1, 2, 2, 2,
							2, 2, 2, 1};

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

void		print_bytes(void *data, int len)
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

unsigned int	*permute_subkey(unsigned long long key)
{
	unsigned int	**ret;

	ret = ft_memalloc(sizeof(unsigned long long *) * 32);
	i = 0;
	while (i < 32)
	{
		ret[i] = ft_memalloc(8);
		i++;
	}
}

unsigned int	*split_subkey(unsigned long long key)
{
	unsigned int	*ret;

	ret = ft_memalloc(2);
	ret[0] = key >> 32;
	ret[1] = key & 4294967295;
	return (ret);
}

uint64_t		subkey(unsigned long long key)
{
	uint64_t	ret;
	size_t		i;
	size_t		tmp;

	i = 0;
	ret = 0;
	while (i < 56)
	{
		tmp = key << g_grab[i];
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
