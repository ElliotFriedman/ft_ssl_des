/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 16:06:46 by efriedma          #+#    #+#             */
/*   Updated: 2018/08/02 14:40:36 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"


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


uint64_t		subkey(unsigned long long key)
{
	uint64_t	ret;
	size_t		i;

	ret = 0;
	i = 0;
	while (i < 56)
	{
	


	}

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

}
