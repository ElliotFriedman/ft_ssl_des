/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 16:06:46 by efriedma          #+#    #+#             */
/*   Updated: 2018/09/25 21:32:48 by efriedma         ###   ########.fr       */
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
size_t		g_salt = 1;

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

int		g_len;
int		g_rotate[16];

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
	while (i < 56)
	{
		tmp = 0;
		 tmp = (pow2(g_grab[i] - 1) & key);
		if ((g_grab[i] + 1) > (int)i)
			tmp <<= (g_grab[i] - i - 1);
		else
			tmp >>= i - (g_grab[i] - 1);
		ret += (tmp);
		i++;
	}
	//least significant 8 bits should be empty
	//ft_printf("\ninit_subkey = %064b\n", ret);
	return (ret);
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

//Account for these with global boolean values

//size_t				g_salt = 1;
size_t				g_passlen;

unsigned long long	*salt_from_file(char *str, size_t len)
{
	size_t			i;

	i = 8;
	if ((!str) || (len < 16))
		return (0);
	if (!ft_strncmp(str, "Salted__", 8))
		return (0);
	//duplicate 8 bytes of memory
	return (ft_memdup((unsigned long long *)str, 8));
}

t_hash				*get_pass_salt(t_hash *file)
{
	FILE	*e;
	char	salt[9];
	char	*pass;
	t_hash	*h;
	unsigned long long	*tmp;

	h = ft_memalloc(sizeof(t_hash));
	e = fopen("/dev/urandom", "r");
	tmp = 0;
	if (!g_key)
		pass = getpass("Enter your password:");
	else
		pass = g_pass;
	//change this later
	//tmp = salt_from_file(file->data, file->bytes);
	if (tmp)
	{
		pass = ft_strjoin(pass, (char*)tmp);
	}
	//data == password
	h->data = ft_strdup(pass);

	h->bytes = ft_strlen(h->data);
	//g_salt will be 3 if we don't want to have added salt
	if (g_salt != 3 && !g_decrypt)
	{
		create_salt_8bytes(salt, e);
		h->data = ft_strjoin(h->data, salt);
		h->bytes += 8;
		ft_putstr("Salted__");
		write(1, salt, 8);
	}
/*	else if (g_decrypt && g_salt)
	{
		//get salt as a string from argv
		//turn to an integer
		//copy bytes from integer to the end of pass using memcpy
		//set g_passlen
		//set h->bytes & h->data
	}
	else if (g_decrypt)
	{
		//find salt from file
		//need access to the file here
		//copy salt bytes from file to end of password
		//set g_passlen
		//set h->bytes & h->data
	}
	*/
	salt[0] = file->data[0];
	fclose(e);
	return (h);
}

void				pbyte(char *str, size_t len)
{
	size_t			i;

	i = 0;
	while (i < len)
	{
		ft_putchar(str[i]);
		i++;
	}
	ft_putstr("\n");
}

void    print_spec(char *str, size_t bytes);

void				removepadbytes(char *str)
{
	size_t	i;
	size_t	hold;
	
	i = 7;
	//ft_printf("%c%c%c%c%c%c%c%c", str[0], str[1], str[2], str[3], str[4], str[5], str[6], str[7]);
	hold = (size_t)(str[i] & 15);
	if (hold == 0 || hold > 8)
	{
		ft_printf("Bad byte pattern found in padding byte(s) ascii val %d found\n", str[i]);
	//	exit(0);
	}
	//ft_printf("g_len: %d, removing bytes %u\n", g_len, hold);
	g_len -= hold;//(hold == 6 ? hold : hold * 2);
	//zero out padding bytes
	while (i < 8 && ((str[i] & 15) == (hold & 15)))
	{
	//	g_len--;
		str[i] = 0;
		i--;
	}
	//ft_printf("updated g_len: %d, removing bytes %u\n", g_len, hold);
}

void			checkbase64encode(char *str, size_t bytes)
{
	size_t			i;

	i = 0;
	if (str[bytes - 1] == '\n')
		bytes--;
	while (i < bytes)
	{
		if (((!ft_strchr(g_ref, str[i]) && str[i] != '=') || bytes % 4 != 0) && str[i] != '\n')
		{
			ft_putstr("Error, invalid byte sequence detected in base64 encoded string\n");
			//exit(0);
		}
		i++;
	}
}

void				inputsanitycheck(t_hash *h)
{
	if (h->bytes % 8 != 0)
	{
		ft_putstr("Error, invalid byte amount in file staged for decryption\n");
		exit(0);
	}
}

void				des(char **argv, int argc)
{
	unsigned long long	*tmp;
	unsigned long long	*key;
	static t_hash		h;
	static t_opt		opt;
	
	//this has been modified and it will return a constant value.
		//try to read the last arg in to encrypt it
//	ft_printf("key befor endian: %064b\n", key[0]);
	
	//make this architecture specific
	//if we are dealing with big endian we will have to do this
	//rev_8byte((char*)key, 8);
	int i = 2;
	
	//get all options
	//aggregate and make choice on where to read data
	get_opt_loop(2, argc, argv, &opt);

	tmp = 0;
	int gbool = 0;
	if (!ft_fread(argv[argc - 1], &h))
	{
		ft_printf("Error, file \'%s\' not found\n", argv[argc - 1]);
		exit(0);
	}
	if (opt.a && g_decrypt)
	{
		char *tmp1 = h.data;
		removewhitespace(h.data);
		h.bytes = ft_strlen(h.data);
		ft_printf("Data is %d bytes\n", h.bytes);
		checkbase64encode(h.data, h.bytes);
		h.data = (char*)base64_decode((unsigned char*)h.data, h.bytes);
		if (!gbool)
			free(tmp1);
		h.bytes = g_b64;
	}
	if (g_decrypt)
	{
		//sanity check here to make sure that the input file was not malformed
		//this will need to be checked whether base64 encoded or not
		inputsanitycheck(&h);
	}
	//now we find the salt in the file, OR,
	//we generate our own depending on what
	//the user specifies
	//char *salt = find_salt();
	tmp = create_key(get_pass_salt(&h));
	key = tmp;
	tmp++;
	tmp = des_encrypt(key[0], h.data, h.bytes);
	if (g_decrypt)
	{
		char *n = (char *)&tmp[(g_len / 8) - 1];
		removepadbytes(n);
	}
	char *out = 0;
	if (opt.a && !g_decrypt)
	{
		out = (char*)base64_encode((unsigned char*)tmp, g_len);
		ft_printf("%s\n", out);
	}
	i = 0;
	char	*str;
	str = (char*)&tmp[(g_len / 8) - 1];
	if (i < g_len && (!opt.a || g_decrypt))
	{
		str = (char *)&tmp[0];
		write(1, str, g_len); 
	}
	free(tmp);
	 //ft_printf("glen is %d bytes\n", g_len);
//	if (!g_decrypt && opt.a)
//		ft_putstr("\n");
}
