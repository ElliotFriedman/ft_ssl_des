/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 13:29:03 by efriedma          #+#    #+#             */
/*   Updated: 2018/09/14 23:48:42 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

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
	int		bit_len;
	int		m;
	size_t	i;
	unsigned char	*n;
	g_pad = ((len * 8) % 3);

	bit_len = findb_len(len);

	n = ft_memalloc(bit_len + 1);
	i = 0;
	m = 0;
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
	//	g_len = (int)ft_strlen((char*)n);
	return (n);
}

void                pbyte(char *str, size_t len);
void    print_spec(char *str, size_t bytes);

void			base64start(char **argv, int argc)
{
	static t_opt	opt;
	unsigned char	*h;
	static t_hash	stor;

	//Handle options -d decode
	//				 -e encode
	//				 -i input file
	//				 -o output file
	h = 0;
	get_opt_loop(1, argc, argv, &opt);
	if (argc == 2)
	{
		if (!rstdin(&stor))
			rkey(&stor);
		//
		//ft_putstr(stor.data);
		removewhitespace(stor.data);
		//
		//ft_putstr(stor.data);
		h = (unsigned char *)stor.data;
		h = base64_encode((unsigned char*)stor.data, ft_strlen((char*)h));
		ft_printf("%s\n", (char*)h);
	}
	else if (argc == 3 && opt.d)
	{
		rkey(&stor);
		//
		//ft_putstr(stor.data);
		removewhitespace(stor.data);
		//
		//ft_putstr(stor.data);
		h = (unsigned char *)stor.data;
		h = base64_decode((unsigned char*)stor.data, ft_strlen((char*)h));
		ft_printf("%s\n", (char*)h);
	}
	else if (argc > 2 && opt.d)
	{
		removewhitespace(argv[argc - 1]);
		h = base64_decode((unsigned char *)argv[argc - 1], ft_strlen(argv[argc - 1]));
		//ft_putstr((char*)h);
		print_spec((char*)h, g_b64);
	}
	else
	{
		h = base64_encode((unsigned char *)argv[argc - 1], ft_strlen(argv[argc - 1]));
		//print_spec((char*)h, g_b64);
		ft_printf("%s\n", (char*)h);
	}
	free(h);
}
