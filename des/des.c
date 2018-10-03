/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 16:06:46 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/02 23:35:55 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

char						*g_tmp;
extern unsigned long long	g_key;
char						*g_saltchars;
int							g_saltcharbool;
extern int					g_b64;
extern int					g_decrypt;
extern int					g_cbc;
extern int					g_out;
size_t						g_strlen;
extern size_t				g_saltbool;
int							g_K;
size_t						g_ivBool;
size_t						g_salt = 1;
extern size_t				g_nosalt;
char						*g_pass;
size_t						g_fileidx;
int							g_grab[56] = {57, 49, 41, 33, 25, 17, 9,
	1, 58, 50, 42, 34, 26, 18,
	10, 2, 59, 51, 43, 35, 27,
	19, 11, 3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	7, 62, 54, 46, 38, 30, 22,
	14, 6, 61, 53, 45, 37, 29,
	21, 13, 5, 28, 20, 12, 4};
int							g_permute[64];
int							g_len;
int							g_rotate[16];

unsigned long long			pow2(size_t amt)
{
	unsigned long long int	ret;

	ret = 9223372036854775808ul;
	while (amt--)
		ret >>= 1;
	return (ret);
}

unsigned long long			init_subkey(unsigned long long key)
{
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
	return (ret);
}

void						swap_4bytes(int *data)
{
	int	a;

	a = data[0];
	data[0] = data[1];
	data[1] = a;
}

void						print_bytes(unsigned long long *data, int len)
{
	size_t				i = 0;
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

unsigned int				*split_subkey(unsigned long long key)
{
	unsigned int	*ret;

	ret = ft_memalloc(2);
	ret[0] = key >> 32;
	ret[1] = key & 4294967295;
	return (ret);
}

unsigned long long			sub_block(unsigned long long key)
{
	unsigned long long		ret;
	size_t					i;
	size_t					tmp;

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

int							char_rand0(FILE *e)
{
	unsigned int			a;

	a = (unsigned int)getc(e);
	while ((a & 127) < 32)
		a += (unsigned int)getc(e);
	return ((int)a);
}

void						create_salt_8bytes(char *salt, FILE *e)
{
	int		i;

	i = 0;
	while (i < 8)
	{
		salt[i] = (char)char_rand0(e) & 127;
		i++;
	}
	salt[8] = 0;
}

size_t						g_passlen;

void						get_user_pass(char **pass, t_hash *file)
{
	char					*tmpa;

	*pass = ft_strdup(getpass("Enter your password:"));
	tmpa = ft_strdup(getpass("Verifying - Enter your password:"));
	if (ft_strcmp(*pass, tmpa) != 0)
	{
		ft_putstr("Verify failure\nbad password read\n");
		free(tmpa);
		free(*pass);
		free(file->data);
		exit(0);
	}
}

char						*getsalt(t_hash *h, char *salt)
{
	char					*tmp;
	FILE					*e;

	tmp = 0;
	e = fopen("/dev/urandom", "r");
	create_salt_8bytes(salt, e);
	if (!g_nosalt)
	{
		h->data = ft_memjoin(h->data, salt, ft_strlen(h->data), 8);
		h->bytes += 8;
	}
	if (!g_decrypt)
	{
		tmp = ft_strjoin("Salted__", salt);
	}
	fclose(e);
	return (tmp);
}

void						handle_salt_add(t_hash *h)
{
	char					*ftmp;

	ftmp = h->data;
	h->data = ft_memjoin(h->data, &g_salt, h->bytes, 8);
	h->bytes += 8;
	free(ftmp);
}

void						create_salt(t_hash *h, char *salt)
{
	g_saltchars = getsalt(h, salt);
	g_saltcharbool = 1;
}

t_hash						*get_pass_salt(t_hash *file)
{
	char					salt[9];
	char					*pass;
	t_hash					*h;

	h = ft_memalloc(sizeof(t_hash));
	pass = 0;
	//if we don't have a password or key, go get one
	if (!g_key)
	{
		get_user_pass(&pass, file);//, tmp);
		g_pass = pass;
	}
	//otherwise, use the current password
	else
	{
		pass = g_pass;
		h->data = ft_strdup(pass);
		h->bytes = ft_strlen(h->data);
	}
	//if no salt has been provided, we haven't said nosalt, and you are not decrypting, get your own salt
	if (!g_nosalt && !g_decrypt && !g_saltbool)
		create_salt(h, salt);
	//otherwise, join salt you already have with password
	else if (!g_nosalt && g_saltbool)
		handle_salt_add(h);
	return (h);
}

void						pbyte(char *str, size_t len)
{
	size_t					i;

	i = 0;
	while (i < len)
	{
		ft_putchar(str[i]);
		i++;
	}
	ft_putstr("\n");
}

void						removepadbytes(char *str)
{
	size_t					i;
	size_t					hold;

	i = 7;
	hold = (size_t)(str[i] & 15);
	if (hold == 0 || hold > 8)
	{
		ft_putstr("Bad byte pattern found in padding byte(s)");
		ft_printf(" ascii val %d found\n", str[i]);
		exit(0);
	}
	g_len -= hold;
	while (i < 8 && ((str[i] & 15) == (hold & 15)))
	{
		str[i] = 0;
		i--;
	}
}

void						checkbase64encode(char *str, size_t bytes)
{
	size_t					i;

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

void						inputsanitycheck(t_hash *h)
{
	if (h->bytes % 8 != 0)
	{
		ft_putstr("Error, invalid byte amount in file staged for decryption\n");
		exit(0);
	}
}

int							g_KEY;

int							archbigendian(void)
{
	int						a;
	char					*b;

	a = 1;
	b = (char*)&a;
	if (*b == 1)
		return (0);
	return (1);
}

void						handle_b64decrypt(t_hash *h)
{
	char					*tmp1;

	tmp1 = h->data;
	removewhitespace(h->data);
	h->bytes = ft_strlen(h->data);
	checkbase64encode(h->data, h->bytes);
	h->data = (char*)base64_decode((unsigned char*)h->data, h->bytes);
	free(tmp1);
	h->bytes = g_b64;
}

void						checkfile(int argc, char **argv, t_hash *h, t_opt *opt)
{
	if (!g_fileidx)
		rkey(h);
	else if ((int)g_fileidx >= argc)
		err0r("Invalid file index\n");
	else if (!ft_fread(argv[g_fileidx], h))
	{
		ft_printf("Error, file \'%s\' not found\n", argv[argc - 1]);
		exit(0);
	}
	if (opt->a && g_decrypt)
		handle_b64decrypt(h);
	if (g_decrypt)
		inputsanitycheck(h);
}

void						printout(unsigned long long *tmp)
{
	g_tmp = (char *)&tmp[0];
	write(g_out, g_tmp, g_len);
	fchmod(g_out, 00000700);	
	close(g_out);
}

void						printouta(unsigned long long *tmp)
{
	g_tmp = (char*)base64_encode((unsigned char*)tmp, g_len);
	ft_putstr_fd(g_tmp, g_out);
	ft_putstr_fd("\n", g_out);
	free(g_tmp);
	exit(0);
}

void						des(char **argv, int argc)
{
	unsigned long long		*tmp;
	unsigned long long		*key;
	static t_hash			h;
	static t_opt			opt;

	get_opt_loop(2, argc, argv, &opt);
	tmp = 0;
	checkfile(argc, argv, &h, &opt);
	if (g_K != 99999999)
		tmp = create_key(get_pass_salt(&h));
	else if (g_K == 99999999 && g_ivBool != 1 && !g_decrypt)
	{
		ft_putstr("Error, no iv specified\n");
		exit(0);
	}
	else
		tmp = &g_key;
	key = tmp;
	tmp++;
	tmp = des_encrypt(key[0], h.data, h.bytes);
	if (g_decrypt)
	{
		g_tmp = (char *)&tmp[(g_len / 8) - 1];
		removepadbytes(g_tmp);
	}
	if (opt.a && !g_decrypt)
		printouta(tmp);
	g_tmp = (char*)&tmp[(g_len / 8) - 1];
	if (g_len && (!opt.a || g_decrypt))
		printout(tmp);
	free(g_tmp);
}
