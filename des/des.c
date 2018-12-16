/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 16:06:46 by efriedma          #+#    #+#             */
/*   Updated: 2018/12/15 21:56:27 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

size_t						g_passlen;
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
int							g_ka;
size_t						g_ivbool;
size_t						g_salt = 1;
extern size_t				g_nosalt;
char						*g_pass;
size_t						g_fileidx;

int							g_permute[64];
int							g_len;
int							g_rotate[16];

extern int					g_b64;

void						checkfile(int argc,
		char **argv,
		t_hash *h,
		t_opt *opt)
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
	{
		inputsanitycheck(h);
		checksalt(h);
	}
}

void						printout(unsigned long long *tmp)
{
	g_tmp = (char *)&tmp[0];
	write(g_out, g_tmp, g_len);
	fchmod(g_out, 00644);
	close(g_out);
}

void						printouta(unsigned long long *tmp)
{
	unsigned long long		*tfree;

	tfree = tmp;
	g_tmp = (char*)base64_encode((unsigned char*)tmp, g_len);
	ft_putstr_fd(g_tmp, g_out);
	ft_putstr_fd("\n", g_out);
	fchmod(g_out, 00644);
	if (g_out != 1)
		close(g_out);
}

void						decryptremovepad(unsigned long long *tmp)
{
	if (!g_len)
		g_len = 8;
	g_tmp = (char *)&tmp[(g_len / 8) - 1];
	removepadbytes(g_tmp);
}

void						des(char **argv, int argc)
{
	unsigned long long		*tmp;
	static t_hash			h;
	static t_opt			opt;

	get_opt_loop(2, argc, argv, &opt);
	tmp = 0;
	checkfile(argc, argv, &h, &opt);
	if (g_ka != 99999999)
		tmp = create_key(get_pass_salt());
	else if (g_ka == 99999999 && g_ivbool != 1 && !g_decrypt && g_cbc)
		iverror();
	else
		tmp = &g_key;
	g_key = *tmp;
	freetmp(tmp);
	tmp = des_encrypt(g_key, h.data, h.bytes);
	if (g_decrypt)
		decryptremovepad(tmp);
	if (opt.a && !g_decrypt)
		printouta(tmp);
	if (g_len && (!opt.a || g_decrypt))
		printout(tmp);
	free(g_tmp);
}
