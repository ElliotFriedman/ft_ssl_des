/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 01:30:08 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/10 02:16:25 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

extern int					g_argc;
extern int					g_out;
extern const char			g_ref[64];
extern int					g_pad;
extern int					g_fd;
extern int					g_len;
extern int					g_b64;
extern size_t				g_fileidx;
extern int					g_bit_len;

int				findb_len(int len)
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

void			initb64vars(int len, size_t *i, int *m)
{
	g_pad = ((len * 8) % 3);
	*i = 0;
	*m = 0;
	g_bit_len = findb_len(len);
}

unsigned char	*base64_encode(unsigned char *s, int len)
{
	int				m;
	size_t			i;
	unsigned char	*n;

	initb64vars(len, &i, &m);
	n = ft_memalloc(g_bit_len + 8);
	add2bytes(&s, len);
	while ((int)i < g_bit_len)
	{
		n[i] = g_ref[(s[m] & 252) >> 2];
		n[i + 1] = g_ref[(((s[m] & 3) << 4) | ((s[m + 1] & 240) >> 4))];
		n[i + 2] = g_ref[(((s[m + 1] & 15) << 2) | (((s[m + 2] & 192) >> 6)))];
		n[i + 3] = g_ref[(s[m + 2] & 63)];
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

void			choice00(unsigned char *h, t_hash *stor)
{
	if (!rstdin(stor))
		rkey(stor);
	h = (unsigned char *)stor->data;
	h = base64_encode((unsigned char*)stor->data, ft_strlen((char*)h));
	ft_putstr((char*)h);
	ft_putstr("\n");
	free(h);
}
