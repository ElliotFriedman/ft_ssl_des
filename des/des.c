/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 16:06:46 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/01 23:37:28 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

// boolean for key provided
extern unsigned long long	g_key;
extern int					g_b64;
extern int					g_decrypt;
extern int					g_cbc;
size_t						g_strlen;
extern size_t				g_saltbool;
int							g_K;
size_t						g_ivBool;
//boolean for whether or not we need to salt
//doubles as a salt value if they specify salt. we convert their string to a ull and store here
size_t						g_salt = 1;
extern size_t				g_nosalt;
//if pass is provided store it here
char						*g_pass;// = "hello";
size_t						g_fileidx;
//this is for key permutation
//
//Turns key from 64 bits to 56 bits.
//
//Since there is no data type that is 56 bits, we will ignore the least significant byte which will be all 0's
//
//This permuted key will be divided into 2 28 bit halves that will be permuted once per round
//
//16 rounds per 64 bit block

int				g_grab[56] = {57, 49, 41, 33, 25, 17, 9,
	1, 58, 50, 42, 34, 26, 18,
	10, 2, 59, 51, 43, 35, 27,
	19, 11, 3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15, //value: 23, index: 33
	7, 62, 54, 46, 38, 30, 22,
	14, 6, 61, 53, 45, 37, 29,
	21, 13, 5, 28, 20, 12, 4};


//This is the initial Permutation done on plaintext

int				g_permute[64];/* = {58, 50, 42, 34, 26, 18, 10,
	2, 60, 52, 44, 36, 28, 20,
	12, 4, 62, 54, 46, 38, 30,
	22, 14, 6, 64, 56, 48, 40,
	32, 24, 16, 8, 57, 49, 41,
	33, 25, 17, 9, 1, 59, 51,
	43, 35, 27, 19, 11, 3, 61,
	53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7};*/

int				g_len;
int				g_rotate[16];

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

void				get_user_pass(char **pass, t_hash *file, unsigned long long *tmp)
{
	char *tmpa;

	*pass = ft_strdup(getpass("Enter your password:"));
	tmpa = ft_strdup(getpass("Verifying - Enter your password:"));
	//ft_printf("pass1: %s\npass2: %s\n", pass, tmpa);
	if (ft_strcmp(*pass, tmpa) != 0)
	{
		ft_putstr("Verify failure\nbad password read\n");
		free(tmpa);
		free(*pass);
		free(tmp);
		free(file->data);
		exit(0);
	}
}

char				*getsalt(t_hash *h, FILE *e, char *salt)//, t_opt *opt)
{
	char			*tmp;

	tmp = 0;
	create_salt_8bytes(salt, e);
	h->data = ft_memjoin((void*)h->data, (void*)salt, ft_strlen(h->data), 8);
	
	h->bytes += 8;
	if (!g_decrypt)
	{
		tmp = ft_strjoin("Salted__", salt);
		//h->data = ft_memjoin(h->data, tmp, h->bytes, 16);

        //ft_printf("Salted beginning of string %s\n", h->data);
	//	h->bytes += 16;
//		ft_putstr("Salted__");
//		write(1, salt, 8);
	}
/*	else if (opt->a && !g_decrypt)
	{
		h->data = ft_strjoin(ft_strdup("Salted__"), salt);
		ft_printf("Salted beginning of string %s\n", h->data);
		h->bytes += 16;
	}
	*/
	//this is the thing that needs to go at the top of the file
	return (tmp);
//	print_bytes((unsigned long long*)salt, 8);
}

char				*g_saltchars;
int					g_saltcharbool;

t_hash				*get_pass_salt(t_hash *file, t_opt *opt)
{
	FILE	*e;
	char	salt[9];
	char	*pass;
	t_hash	*h;
	unsigned long long	*tmp;

	h = ft_memalloc(sizeof(t_hash));
	e = fopen("/dev/urandom", "r");
	tmp = 0;
	pass = 0;
	opt->on = 1; 
	if (!g_key)
	{
		get_user_pass(&pass, file, tmp);
		g_pass = pass;
	}
	else
	{
		pass = g_pass;
		h->data = ft_strdup(pass);
		h->bytes = ft_strlen(h->data);
	}
	//if no salt has been provided, get your own salt
	if (!g_nosalt && !g_decrypt && !g_saltbool)
	{
		g_saltchars = getsalt(h, e, salt);
		g_saltcharbool = 1;
	}
	//otherwise, join salt you already have with password
	else if (g_nosalt && g_saltbool)// && !g_decrypt)
	{
		char *ftmp;

		ftmp = h->data;
		h->data = ft_memjoin(h->data, &g_salt, h->bytes, 8);
		h->bytes += 8;
		free(ftmp);
	}
	//salt[0] = file->data[0];
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
	hold = (size_t)(str[i] & 15);
	if (hold == 0 || hold > 8)
	{
		ft_printf("Bad byte pattern found in padding byte(s) ascii val %d found\n", str[i]);
		exit(0);
	}
	g_len -= hold;
	//zero out padding bytes
	while (i < 8 && ((str[i] & 15) == (hold & 15)))
	{
		str[i] = 0;
		i--;
	}
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
			exit(0);
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

int					g_KEY;

int					archBigEndian(void)
{
	int				a;
	char			*b;

	a = 1;
	b = (char*)&a;
	if (*b == 1)
		return (0);
	return (1);
}

void				handle_b64decrypt(t_hash *h)
{
	char *tmp1;

	tmp1 = h->data;
	removewhitespace(h->data);
	h->bytes = ft_strlen(h->data);
//	ft_printf("Data is %d bytes\n", h->bytes);
	checkbase64encode(h->data, h->bytes);
	h->data = (char*)base64_decode((unsigned char*)h->data, h->bytes);
	free(tmp1);
	h->bytes = g_b64;
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

	int i = 2;
	//get all options
	//aggregate and make choice on where to read data
	get_opt_loop(2, argc, argv, &opt);

	tmp = 0;
	if (g_K != 99999999)
		tmp = create_key(get_pass_salt(&h, &opt));
	if (!g_fileidx)
		rkey(&h);
	else if ((int)g_fileidx >= argc)
		err0r("Invalid file index\n");
	else if (!ft_fread(argv[g_fileidx], &h))
	{
		ft_printf("Error, file \'%s\' not found\n", argv[argc - 1]);
		exit(0);
	}
	if (opt.a && g_decrypt)
	{
//		handle_b64decrypt(&h);
		char *tmp1 = h.data;
		removewhitespace(h.data);
		h.bytes = ft_strlen(h.data);
		ft_printf("Data is %d bytes\n", h.bytes);
		checkbase64encode(h.data, h.bytes);
		h.data = (char*)base64_decode((unsigned char*)h.data, h.bytes);
		free(tmp1);
		h.bytes = g_b64;
	}
	if (g_decrypt) //sanity check here to make sure that the input file was not malformed//this will need to be checked whether base64 encoded or not
		inputsanitycheck(&h);
	//now we find the salt in the file, OR,
	//we generate our own depending on what
	//the user specifies
//	if (g_K != 99999999)
//		tmp = create_key(get_pass_salt(&h, &opt));
	else if (g_K == 99999999 && g_ivBool != 1 && !g_decrypt)
	{
		ft_putstr("Error, no iv specified\n");
		exit(0);
	}
	else
		tmp = &g_key;
	key = tmp;
	if (archBigEndian())
		rev_8byte((char*)key, 8);
//	printf("key provided %016llX\n", *key);
	tmp++;
	tmp = des_encrypt(key[0], h.data, h.bytes);
	if (g_saltcharbool)
	{
//		ft_putstr(g_saltchars);
//		ft_putstr("\n");
		tmp = (unsigned long long *)ft_memjoin(g_saltchars, tmp, 16, g_len);
		//h.bytes += 16;
		g_len += 15;
	}
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
