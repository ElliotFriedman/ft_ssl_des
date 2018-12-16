/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 13:29:03 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/16 22:05:36 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

int					g_argc;
extern int			g_out;
const char			g_ref[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ\
abcdefghijklmnopqrstuvwxyz0123456789+/";
int					g_pad;
int					g_fd;
int					g_len;
int					g_b64;
extern size_t		g_fileidx;
int					g_bit_len;
int					g_t;

unsigned char	*handle_i(char **argv, t_hash *stor, t_opt *opt, size_t i)
{
	unsigned char	*h;

	if (!i && !rstdin(stor))
	{
		ft_putstr("Error, no input\n");
		exit(0);
	}
	if (i + 1 == (size_t)g_argc)
		err0rr('i');
	else if (!ft_fread(argv[i + 1], stor))
	{
		ft_putstr("Unable to open ");
		ft_printf("'%s': No such file or directory\n", argv[i + 1]);
		exit(0);
	}
	h = (unsigned char *)stor->data;
	if (!opt->d)
		h = base64_encode((unsigned char*)stor->data, stor->bytes);
	else
	{
		removewhitespace(stor->data);
		h = base64_decode((unsigned char*)stor->data, ft_strlen(stor->data));
	}
	return (h);
}

void			handle_o(t_hash *stor, t_opt *opt, unsigned char *h1)
{
	unsigned char	*h;

	h = (unsigned char *)stor->data;
	if (opt->d)
		h = base64_decode((unsigned char*)stor->data, ft_strlen((char*)h));
	else
		h = base64_encode((unsigned char*)stor->data, stor->bytes);
	write(g_out, (char*)h, g_b64);
	write(g_out, "\n", 1);
	close(g_out);
	if (h1)
		free(h1);
	free(h);
}

void			handle_printing(unsigned char *h, t_opt *opt)
{
	if (h)
		write(1, (char*)h, g_b64);
	if (!opt->d)
		write(g_out, "\n", 1);
	if (h)
		free(h);
}

void			find_options(char **argv, int argc, t_hash *stor, t_opt *opt)
{
	int				i;
	unsigned char	*h;
	unsigned char	*h2;

	i = -1;
	h = 0;
	h2 = 0;
	while (++i < argc)
		if (!ft_strncmp(argv[i], "-i", 2) && ++g_t)
			h = (unsigned char*)handle_i(argv, stor, opt, i);
	i = -1;
	if (!g_t && !rstdin(stor))
		rkey(stor);
	while (++i < argc)
	{
		if (!ft_strncmp(argv[i], "-o", 2))
		{
			if (i + 1 == argc)
				err0rr('o');
			handle_o(stor, opt, h);
			return ;
		}
	}
	handle_printing(h, opt);
}

void			base64start(char **argv, int argc)
{
	static t_opt	opt;
	unsigned char	*h;
	static t_hash	stor;

	h = 0;
	g_argc = argc;
	get_opt_loop(1, argc, argv, &opt);
	if (argc == 2)
		choice00(h, &stor);
	else if (argc == 3 && opt.d)
		choice01(h, &stor);
	else if (argc >= 3)
		find_options(argv, argc, &stor, &opt);
}
