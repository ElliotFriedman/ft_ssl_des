/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 16:06:46 by efriedma          #+#    #+#             */
/*   Updated: 2018/08/01 18:04:49 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

int			_rand0(void)
{
	unsigned int	a;
	int				fd;
	FILE			*e;	

	a = 0;
	ft_printf("\n\nhere in rand\n\n");
	if ((e = fopen("/dev/random", "r")))
	{
	//	
		ft_printf("open success fd: %d, char %u\n", fd, a);
		while ((a & 255) < 32)
		{
			ft_printf("Stuck here\n");
			a += (unsigned int)getc(e);
		}
	}
	ft_printf("fd: %d\n", fd);
	return ((int)a);
}

void		create_salt(char *salt)
{
	//use /dev/random
	int		i;

	i = 0;
	ft_printf("Hi\n");
	while (i < 8)
	{
		ft_printf("Here forever\n");
		salt[i] = (char)_rand0();
		i++;
	}
	ft_printf("exiting create_salt\n");
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
