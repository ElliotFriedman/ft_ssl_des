/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 13:29:03 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/04 02:47:56 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

int			g_argc;

const char	g_ref[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
int			g_pad;
int			g_fd;
int			g_len;
int			g_b64;

int	findb_len(int len)
{
	int	t_bits;

	t_bits = len;
	while (t_bits % 3 != 0)
		t_bits++;
	return ((t_bits / 3) * 4);
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
	//add 2 bytes to string
	str = (unsigned char*)ft_memjoin((void*)str, 0, len, 0);
	str = (unsigned char*)ft_memjoin((void*)str, 0, ++len, 0);
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
	//	ft_printf("%d\n", g_b64);
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
//	fd_putstr("\n", 1, 1);
}

void			err0rr(char error)
{
	ft_printf("base64: option requires an argument -- %c\n", error);
	ft_putstr("Usage:	base64 [-hvD] [-b num] [-i in_file] [-o out_file]\n");
	ft_putstr("	-d, --decode   decodes input\n  -i, --input    input file ");
	ft_putstr("(default: \"-\" for stdin)\n  -o, --output   output file (default: \"-\" for stdout)\n");
	exit(0);
}

unsigned char	*handle_i(char **argv, t_hash *stor, t_opt *opt, size_t i)
{
	unsigned char	*h;

	opt->i = 1;
	if (i + 1 == (size_t)g_argc)
		err0rr('i');
	else if (!ft_fread(argv[i + 1], stor))
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

void			find_options(char **argv, int argc, t_hash *stor, t_opt *opt)
{
	int				i;
	unsigned char	*h;
	int				fd;
	unsigned char	*h2;

	fd = 1;
	i = -1;
	h = 0;
	h2 = 0;
	while (++i < argc)
	{
		if (!ft_strncmp(argv[i], "-i", 2))
			h = (unsigned char*)handle_i(argv, stor, opt, i);
		if (!ft_strncmp(argv[i], "-o", 2))
		{
			if (i + 1 == argc)
					err0rr('o');
			fd = open(argv[i + 1], O_WRONLY | O_CREAT);
			ft_printf("FD: %d\n", fd);
			h2 = (unsigned char*)handle_o(stor, opt);
			write(fd, (char*)h2, g_b64);
			fd_putstr("\n", fd, 1);
			close(fd);
			free(h2);
			return ;
		}
	}
	fd_putstr((char*)h, 1, g_b64);
	if (!opt->d)
		fd_putstr("\n", 1, fd);
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
