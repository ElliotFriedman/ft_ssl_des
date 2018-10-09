/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 13:29:03 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/09 01:28:47 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

int							g_argc;
extern int			g_out;

const char			g_ref[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
int							g_pad;
int							g_fd;
int							g_len;
int							g_b64;
extern size_t		g_fileidx;

int	findb_len(int len)
{
	int	t_bits;

	t_bits = len;
	while (t_bits % 3 != 0)
		t_bits++;
	return ((t_bits / 3) * 4);
}

void			add2bytes(unsigned char **str, int len)
{
	unsigned char	*tmp;

	tmp = *str;
	*str = (unsigned char*)ft_memjoin((void*)*str, 0, len, 0);
	free(tmp);
	tmp = *str;
	*str = (unsigned char*)ft_memjoin((void*)*str, 0, ++len, 0);
	free(tmp);
}

unsigned char	*base64_encode(unsigned char *str, int len)
{
	int				bit_len;
	int				m;
	size_t			i;
	unsigned char	*n;

	g_pad = ((len * 8) % 3);
	bit_len = findb_len(len);
	n = ft_memalloc(bit_len + 8);
	i = 0;
	m = 0;
	add2bytes(&str, len);
//	str = (unsigned char*)ft_memjoin((void*)str, 0, len, 0);
//	str = (unsigned char*)ft_memjoin((void*)str, 0, ++len, 0);
	while ((int)i < bit_len)
	{
		n[i] = g_ref[(str[m] & 252) >> 2];
		n[i + 1] = g_ref[(  ((str[m] & 3) << 4) |  ((str[m + 1] & 240) >> 4))];
		n[i + 2] = g_ref[(  ((str[m + 1] & 15) << 2)   |   (((str[m + 2] & 192) >> 6))   )];
		n[i + 3] = g_ref[(     str[m + 2] & 63  )];
		m += 3;
		i += 4;
	}
	i -= g_pad;
	while (g_pad)
	{
		n[i] = '=';
		i++;
		g_pad--;
	}
	g_b64 = (int)ft_strlen((char*)n);
	return (n);
}

void                pbyte(char *str, size_t len);
void    print_spec(char *str, size_t bytes);

void			choice00(unsigned char *h, t_hash *stor)
{
	if (!rstdin(stor))
		rkey(stor);
	h = (unsigned char *)stor->data;
	h = base64_encode((unsigned char*)stor->data, ft_strlen((char*)h));
	ft_putstr((char*)h);
	ft_putstr("\n");
}

void	fd_putstr(char *str, int fd, int len)
{
	write(fd, str, len);
}

void			choice01(unsigned char *h, t_hash *stor)
{
	rkey(stor);
	removewhitespace(stor->data);
	h = (unsigned char *)stor->data;
	h = base64_decode((unsigned char*)stor->data, ft_strlen((char*)h));
	fd_putstr((char*)h, 1, g_b64);
}

void			err0rr(char error)
{
	ft_printf("base64: option requires an argument -- %c\n", error);
	ft_putstr("Usage:	base64 [-hvD] [-b num] [-i in_file] [-o out_file]\n");
	ft_putstr("	-d, --decode   decodes input\n  -i, --input    input file ");
	ft_putstr("(default: stdin)\n  -o, --output   output file (default: stdout)\n");
	exit(0);
}

unsigned char	*handle_i(char **argv, t_hash *stor, t_opt *opt, size_t i)
{
	unsigned char	*h;

	opt->i = 1;
	if (!i && !rstdin(stor))
	{
		ft_putstr("Error, no input\n");
		exit(0);
	}
	if (i + 1 == (size_t)g_argc)
		err0rr('i');
	else if (!ft_fread(argv[i], stor))
	{
		ft_printf("Unable to open '%s': No such file or directory\n", argv[i + 1]);
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

unsigned char   *handle_o(t_hash *stor, t_opt *opt)
{
	unsigned char	*h;

	h = (unsigned char *)stor->data;
	if (opt->d)
		h = base64_decode((unsigned char*)stor->data, ft_strlen((char*)h));
	else
		h = base64_encode((unsigned char*)stor->data, stor->bytes);
	return (h);
}

void     	handle_printing(unsigned char *h, t_opt *opt)
{
	fd_putstr((char*)h, 1, g_b64);
	if (!opt->d)
		fd_putstr("\n", 1, g_out);
}

void 			initvarsb64(int *i, unsigned char **h, unsigned char **h2)
{
		*i = -1;
		*h = 0;
		*h2 = 0;
}

void			find_options(char **argv, int argc, t_hash *stor, t_opt *opt)
{
	int						i;
	unsigned char	*h;
	unsigned char	*h2;

	initvarsb64(&i, &h, &h2);
	//	if (!ft_strncmp(argv[i], "-i", 2))
		//{
			h = (unsigned char*)handle_i(argv, stor, opt, g_fileidx);
			ft_printf("stor->data: %s\n", stor->data);
	//	}
		if (g_out != 1)
		{
			if (i + 1 == argc)
					err0rr('o');
			fchmod(g_out, 00000700);
			//h2 = (unsigned char*)handle_o(stor, opt);
			write(g_out, stor->data, g_b64);
			fd_putstr("\n", g_out, 1);
			close(g_out);
			free(h2);
			return ;
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
	else
	{
		h = base64_encode((unsigned char *)argv[argc - 1], ft_strlen(argv[argc - 1]));
		ft_printf("%s\n", (char*)h);
		free(h);
	}
}
