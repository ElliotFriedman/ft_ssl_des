/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 16:06:46 by efriedma          #+#    #+#             */
/*   Updated: 2018/08/20 00:59:15 by efriedma         ###   ########.fr       */
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
/*
int			g_grab[56] = {57, 49, 41, 33, 25, 17, 9,
	1, 58, 50, 42, 34, 26, 18,
	10, 2, 59, 51, 43, 35, 27,
	19, 11, 3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	7, 62, 54, 46, 38, 30, 22,
	14, 6, 61, 53, 45, 37, 29,
	21, 13, 5, 28, 20, 12, 4};
*/

int			g_grab[56] = {57, 49, 41, 33, 25, 17, 9,
	1, 58, 50, 42, 34, 26, 18,
	10, 2, 59, 51, 43, 35, 27,
	19, 11, 3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15, //value: 23, index: 33
	7, 62, 54, 46, 38, 30, 22,
	14, 6, 61, 53, 45, 37, 29,
	21, 13, 5, 28, 20, 12, 4};


//This is the initial Permutation done on plaintext

int			g_permute[64] = {58, 50, 42, 34, 26, 18, 10,
	2, 60, 52, 44, 36, 28, 20,
	12, 4, 62, 54, 46, 38, 30,
	22, 14, 6, 64, 56, 48, 40,
	32, 24, 16, 8, 57, 49, 41,
	33, 25, 17, 9, 1, 59, 51,
	43, 35, 27, 19, 11, 3, 61,
	53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7};

//rotate subkey x bits left at each round

int		g_rotate[16];

void	m5()
{
	size_t	i = -1;

	ft_putstr("                  ");
	while (++i < 64)
		ft_printf("%d", i % 10);
	ft_putstr("\n");
}

unsigned long long	pow2(size_t amt)
{
	unsigned long long int	ret;

	ret = 9223372036854775808ul;
	while (amt--)
		ret >>= 1;
	ft_printf("pow2   =          %064b\n", ret);
	return (ret);
}
/*
size_t				lut(size_t i)
{
	//shift left by g_grab[i] - i

	if (!i)
		return (g_grab[i]);

}
*/
// ft_printf("shiftr: %02d val:   %064b\n",  g_grab[i] - i - 1,(pow2(g_grab[i] - 1) & key));

unsigned long long	init_subkey(unsigned long long key)
{
	//This is to extract the 56 bit key from 64 bits
	unsigned long long	ret;
	size_t				i;
	unsigned long long	tmp;

	i = 0;
	ret = 0;
	//n = 9223372036854775808ul;
	//ft_printf("tmp bits: ");
	while (i < 56)
	{
		m5();
		tmp = 0;
		  ft_printf("cur pos: %d shift left: %d, shift right: %d i: %d\n",i,  g_grab[i] - i - 1, i - g_grab[i] - 1, i);

		 tmp = (pow2(g_grab[i] - 1) & key);
		  //ft_printf("tmp after shift:  %064b\n", (tmp = (g_grab[i] > (int)i > 0) ? (tmp << (g_grab[i] - i - 1)) : (tmp >> (i - g_grab[i] - 1))));
		if ((g_grab[i] + 1) > (int)i)
			tmp <<= (g_grab[i] - i - 1);
		else
			tmp >>= i - (g_grab[i] - 1);
		ft_printf("tmp after shift:  %064b\n", tmp);
	  	ft_printf("key binary:       %064b\n", key);
		ft_printf("%02d bit =          %064b\n",i, tmp);//(tmp & 1) << i);
		ret += (tmp);
		  ft_printf("Print as we build %064b\n\n", ret);

		i++;
	}
	//least significant 8 bits should be empty
	ft_printf("\ninit_subkey = %064b\n", ret);
	return (ret);
}

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

void		print_bytes(unsigned long long *data, int len)
{
	size_t	i = 0;
	unsigned long long	use;
	unsigned char		*print;

	use = *data;

	print = (unsigned char *)&use;
	while ((int)i < len)
	{
		ft_printf("%02X", print[i]);
		i++;
	}
	ft_putstr("\n");
}

unsigned int		*split_subkey(unsigned long long key)
{
	unsigned int	*ret;

	ret = ft_memalloc(2);
	ret[0] = key >> 32;
	ret[1] = key & 4294967295;
	return (ret);
}

unsigned long long	sub_block(unsigned long long key)
{
	//This is to permute the 64 bit block of text that is passed in
	unsigned long long	ret;
	size_t				i;
	size_t				tmp;

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

char				*get_pass_salt(void)
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
	fclose(e);
	return (ft_strdup(pass));
	//uncomment this for later iterations
//	return (ft_strjoin(pass, salt));
}

//Do key byte orders need to changed to big endian?

void				des(char **argv, int argc)
{
	unsigned long long	*tmp;
	unsigned long long	*key;
	static t_hash		h;

	//this has been modified and it will return a constant value.
	tmp = create_key(get_pass_salt());

	key = tmp;
	ft_putstr("key=");
	//print bytes without reversing byte order in memory
	print_bytes(tmp, 8);
	//ft_printf("key in binary: %064b\n", key[0]);
	tmp++;
	ft_putstr("iv =");
	print_bytes(tmp, 8);
	//try to read the last arg in to encrypt it
	print_bytes(key, 8);
	ft_printf("key befor endian: %064b\n", key[0]);
	//rev_8byte((char*)key, 8);
	//ft_putstr("key=");
	//print_bytes(tmp, 8);
	ft_printf("key after endian: %064b\n", key[0]);
	if (!ft_fread(argv[argc - 1], &h))
		/*ft_printf("%s\n", */des_encrypt(key[0], argv[argc - 1], ft_strlen(argv[argc - 1]));//);
	else
		des_encrypt(key[0], h.data, ft_strlen(h.data));
	//ft_printf("iv in binary: %064b\n", key[1]);
	//do subkey after byte order has been changed to big endian
}
