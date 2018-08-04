/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 16:06:46 by efriedma          #+#    #+#             */
/*   Updated: 2018/08/03 17:01:14 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

// boolean for key provided
int			g_key = 1;
//boolean for whether or not we need to salt
//doubles as a salt value if they specify salt. we convert their string to a ull and store here
unsigned long long	g_salt;
//if pass is provided store it here
char		*g_pass = "hello";

//this is for key permutation
//
//Turns key from 64 bits to 56 bits.
//
//Since there is no data type that is 56 bits, we will ignore the least significant byte which will be all 0's
//
//This permuted key will be divided into 2 28 bit halves that will be permuted once per round
//
//16 rounds per 64 bit block

int			g_grab[56] = {57, 49, 41, 33, 25, 17, 9,
	1, 58, 50, 42, 34, 26, 18,
	10, 2, 59, 51, 43, 35, 27,
	19, 11, 3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	7, 62, 54, 46, 38, 30, 22,
	14, 6, 61, 53, 45, 37, 29,
	21, 13, 5, 28, 20, 12, 4};

int			g_permute[64] = {58, 50, 42, 34, 26, 18, 10,
	2, 60, 52, 44, 36, 28, 20,
	12, 4, 62, 54, 46, 38, 30,
	22, 14, 6, 64, 56, 48, 40,
	32, 24, 16, 8, 57, 49, 41,
	33, 25, 17, 9, 1, 59, 51,
	43, 35, 27, 19, 11, 3, 61,
	53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7};


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
/*
   unsigned int	*permute_subkey(unsigned long long key)
   {
   unsigned int	**ret;
   int				i;

   i = 0;
   ret = ft_memalloc(sizeof(unsigned long long *) * 32);
   i = 0;
   while (i < 32)
   {
   ret[i] = ft_memalloc(8);
   i++;
   }
   }
   */
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

char		*get_pass_salt(void)
{
	FILE	*e;
	char	salt[9];
	char	*pass;

	e = fopen("/dev/urandom", "r");
	if (!g_key)
		pass = getpass("Enter your password:");
	else
		pass = g_pass;
	if (!g_salt)
		create_salt_8bytes(salt, e);

	ft_printf("Random salt: %s\n", salt);
	ft_printf("Password: %s\n", pass);
	fclose(e);
	return (ft_strdup(pass));
	//uncomment this for later iterations
	//return (ft_strjoin(pass, 0));//salt));
}

void		des(char **argv, int argc)
{
	unsigned long long	*tmp;
	unsigned long long	*key;
	//	char 				*pass;
	int					i = 0;

	tmp = create_key(get_pass_salt());
	key = tmp;
	ft_putstr("key = ");
	print_bytes((void*)tmp, 8);
	ft_printf("key in binary: %064b\n", key);
	tmp++;
	ft_putstr("iv =");
	print_bytes((void*)tmp, 8);
	//do subkey after byte order has been changed to big endian
}
