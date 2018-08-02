/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 16:06:46 by efriedma          #+#    #+#             */
/*   Updated: 2018/08/01 18:14:47 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

int			_rand0(void)
{
	unsigned int	a;
	FILE			*e;	

	a = 0;
	if ((e = fopen("/dev/random", "r")))
	{
	//	
		a = (unsigned int)getc(e);
		while ((a & 127) < 32 && a != 48)
		{
			a += (unsigned int)getc(e);
		}
		ft_printf("open success, char %u\n",a);
	}
	return ((int)a);
}

void		create_salt(char *salt)
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

int		main(void)
{
	unsigned long long	*tmp;
	unsigned long long	key[2];
	char 				*pass;
	char				salt[9];
	//parse for all options to decide how to handle

	//have user enter their password
	//
	//store in pass
	//
	//salt is created
	//
	//salt is concatenated on pass
	create_salt(salt);
	
	ft_printf("Random salt: %s\n", salt);

	
//	tmp = create_salt(pass);
//	key[0] = tmp[0];
//	key[1] = tmp[1];
//	ft_memdel((void**)&tmp);
}
