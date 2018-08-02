/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 16:06:46 by efriedma          #+#    #+#             */
/*   Updated: 2018/08/01 18:19:52 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

FILE			*e;	

int			_rand0(void)
{
	unsigned int	a;

	a = 0;
	if ((e = fopen("/dev/urandom", "r")))
	{
		a = (unsigned int)getc(e);
		while ((a & 127) < 32)
		{
			a += (unsigned int)getc(e);
		}
	}
	return ((int)a);
}

void		create_salt_8bytes(char *salt)
{
	//use /dev/random
	int		i;

	i = 0;
	while (i < 8)
	{
		salt[i] = (char)_rand0() & 127;
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
		//ft_printf("%d\n", print[i]);
		ft_printf("%02X", print[i]);
		//ft_printf("i: %d\n", i);
		i++;
	}
	ft_putstr("\n");
}


void		des(char **argv, int argc)
{
	unsigned long long	*tmp;
	unsigned long long	*key;
	char 				*pass;
	char				salt[9];// = malloc(9);
	int		i = 0;

	pass = getpass("Enter your password:");
	//parse for all options to decide how to handle

	//have user enter their password
	//
	//store in pass
	//
	//salt is created
	//
	//salt is concatenated on pass
	//while (i < 30)
	//{

	create_salt_8bytes(salt);
	ft_printf("Random salt: %s\n", salt);
	fclose(e);
	ft_printf("Salt: %02X%02X%02X%02X%02X%02X%02X%02X\n", salt[0], salt[1], salt[2], salt[3], salt[4], salt[5],salt[6], salt[7]);
	//	i++;
	//}

	//for some reason getpass allocates on the stack so you can't free. Hmmm
	//pass = ft_strjoin(pass, salt);
	ft_printf("pass: %s\n", pass);
	tmp = create_key(pass);
	key = tmp;
	ft_putstr("key=");
	print_bytes((void*)tmp, 8);
	tmp++;
	ft_putstr("iv =");
	print_bytes((void*)tmp, 8);

	//free(salt);
}
