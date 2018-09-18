/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 16:06:46 by efriedma          #+#    #+#             */
/*   Updated: 2018/09/17 20:18:03 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

// boolean for key provided
int			g_key = 1;
extern int	g_b64;
extern int	g_decrypt;
extern int	g_cbc;

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

int			g_permute[64];/* = {58, 50, 42, 34, 26, 18, 10,
	2, 60, 52, 44, 36, 28, 20,
	12, 4, 62, 54, 46, 38, 30,
	22, 14, 6, 64, 56, 48, 40,
	32, 24, 16, 8, 57, 49, 41,
	33, 25, 17, 9, 1, 59, 51,
	43, 35, 27, 19, 11, 3, 61,
	53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7};*/

//rotate subkey x bits left at each round

int		g_len;
int		g_rotate[16];

/*
void	m5()
{
	size_t	i = -1;

	ft_putstr("                  ");
	while (++i < 64)
//		ft_printf("%d", i % 10);
	ft_putstr("\n");
}
*/

unsigned long long	pow2(size_t amt)
{
	unsigned long long int	ret;

	ret = 9223372036854775808ul;
	while (amt--)
		ret >>= 1;
	return (ret);
}

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
//		m5();
		tmp = 0;
//		  ft_printf("cur pos: %d shift left: %d, shift right: %d i: %d\n",i,  g_grab[i] - i - 1, i - g_grab[i] - 1, i);
		 tmp = (pow2(g_grab[i] - 1) & key);
		  //ft_printf("tmp after shift:  %064b\n", (tmp = (g_grab[i] > (int)i > 0) ? (tmp << (g_grab[i] - i - 1)) : (tmp >> (i - g_grab[i] - 1))));
		if ((g_grab[i] + 1) > (int)i)
			tmp <<= (g_grab[i] - i - 1);
		else
			tmp >>= i - (g_grab[i] - 1);
//		ft_printf("tmp after shift:  %064b\n", tmp);
//	  	ft_printf("key binary:       %064b\n", key);
//		ft_printf("%02d bit =          %064b\n",i, tmp);//(tmp & 1) << i);
		ret += (tmp);
//		  ft_printf("Print as we build %064b\n\n", ret);

		i++;
	}
	//least significant 8 bits should be empty
	//ft_printf("\ninit_subkey = %064b\n", ret);
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
void				pbyte(char *str, size_t len)
{
	size_t	i = 0;

	while (i < len)
	{
		ft_printf("%02hhX", str[i]);
		//if (((i + 1) % 8) == 0)
		//	ft_putstr(" ");
		i++;
	}
	ft_putstr("\n");
//	i = 0;
/*	char hold;
	while (i < len)
	{
		hold = str[i];
		ft_printf("%08hhb ", (char)hold & 255); 
		i++;
	}
	ft_putstr("\n");
*/
}

void    print_spec(char *str, size_t bytes);

void				removepadbytes(char *str)
{
	size_t	i;
	size_t	hold;
	
	i = 7;
	//sanity check to make sure that padding bytes were valid
	if (str[i] == 0 || str[i] > 8)
	{
		ft_printf("Bad byte pattern found in padding byte(s) ascii val %d found\n", str[i]);
	}
	hold = str[i];
	//zero out padding bytes
	while (hold && i < 8)
	{
		str[i] = 0;
		hold--;
		i--;
	}
}

void				des(char **argv, int argc)
{
	unsigned long long	*tmp;
	unsigned long long	*key;
	static t_hash		h;
	static t_opt		opt;
	
	//this has been modified and it will return a constant value.
	tmp = create_key(get_pass_salt());
	key = tmp;
	tmp++;
	//try to read the last arg in to encrypt it
//	ft_printf("key befor endian: %064b\n", key[0]);
	//rev_8byte((char*)key, 8);
	//ft_putstr("key=");
	int i = 2;
	//replace this with get_opt loop
	while (get_opt(argc, argv, &opt, i))
		i++;
	tmp = 0;
	if (!ft_fread(argv[argc - 1], &h))
	{
		h.data = argv[argc - 1];
		h.bytes = ft_strlen(argv[argc - 1]);
	}
//	else
//		ft_printf("successfully read in this amoutn of bytes:\n%d\n", h.bytes);
	if (opt.a && g_decrypt)
	{
//		ft_printf("\n\n\nDecrypting and translating base64 to bytes\n\n\n\n");
		char *tmp = h.data;
		h.data = (char*)base64_decode((unsigned char*)h.data, h.bytes);
		free(tmp);
		h.bytes = g_b64;
	}
	tmp = des_encrypt(key[0], h.data, h.bytes);
	char *out = 0;
	if (opt.a && !g_decrypt)
	{
		out = (char*)base64_encode((unsigned char*)tmp, g_len);
		ft_printf("\nBase64 ciphertext:\n%s\n\n", out);
	}
//	if (!ft_fread(argv[argc - 1], &h))
//	{
//		ft_printf("\ncould not read, taking last arg as txt block\n\n\n");
		//grab return value for later use
//		tmp = des_encrypt(key[0], ft_strdup(argv[argc - 1]), ft_strlen(argv[argc - 1]));
//	}
//	else
//	{
//		ft_printf("\nRead from a file descriptor, taking last arg as txt block\n\n\n");
		//grab return value for later use
//		tmp = des_encrypt(key[0], h.data, h.bytes);
//	}
	i = 0;
	char	*str;
	str = (char*)&tmp[(g_len / 8) - 1];
	if (g_decrypt)
	{
		removewhitespace(str);
		removepadbytes(str);
	}
//	ft_printf("\n\nG_len: %d\n\n", g_len);
	
	while ((i * 8) < g_len && !opt.a)
	{
		str = (char*)&tmp[i];
		ft_printf("%c%c%c%c%c%c%c%c", str[0], str[1], str[2], str[3], str[4], str[5], str[6], str[7]);
		i++;
	}
	//do subkey after byte order has been changed to big endian
}
