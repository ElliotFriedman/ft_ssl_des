/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 19:18:29 by efriedma          #+#    #+#             */
/*   Updated: 2018/06/27 23:41:16 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

const unsigned int g_ks[64] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

const int g_s[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17,
	22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14,
	20, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16,
	23, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15,
	21};

void	handle_out(t_val new, t_hash *h, t_opt *opt)
{
	unsigned char	*msg;

	if ((opt->on && !opt->s && !opt->q && !opt->r && opt->p && !h->pipe)
			|| (h->fd && !opt->q && !opt->r && !opt->p))
		ft_printf("MD5 (%s) = ", h->name);
	else if (opt->on && opt->s && !opt->q && !opt->r && !h->pipe)
		ft_printf("MD5 (\"%s\") = ", h->name);
	msg = (unsigned char*)&new.a0;
	ft_printf("%02x%02x%02x%02x", msg[0], msg[1], msg[2], msg[3]);
	msg = (unsigned char*)&new.b0;
	ft_printf("%02x%02x%02x%02x", msg[0], msg[1], msg[2], msg[3]);
	msg = (unsigned char*)&new.c0;
	ft_printf("%02x%02x%02x%02x", msg[0], msg[1], msg[2], msg[3]);
	msg = (unsigned char*)&new.d0;
	ft_printf("%02x%02x%02x%02x", msg[0], msg[1], msg[2], msg[3]);
	if (opt->on && opt->s && opt->r && !opt->q && !h->pipe)
		ft_printf(" \"%s\"", h->name);
	else if (!opt->q && !opt->s && opt->r && !h->pipe)
		ft_printf(" %s", h->name);
	ft_putstr("\n");
	h->fd = 0;
}

void	initv(t_val *new)
{
	new->a0 = 0x67452301;
	new->b0 = 0xefcdab89;
	new->c0 = 0x98badcfe;
	new->d0 = 0x10325476;
}

void	initz(t_iter *z, t_val *new)
{
	z->aa = new->a0;
	z->bb = new->b0;
	z->cc = new->c0;
	z->dd = new->d0;
	z->i = -1;
}

void	whilec(t_iter *z, t_hash *h, size_t ctr)
{
	if (z->i <= 15)
	{
		z->ff = (z->bb & z->cc) | ((~z->bb) & z->dd);
		z->g = z->i;
	}
	else if (z->i <= 31)
	{
		z->ff = (z->dd & z->bb) | ((~z->dd) & z->cc);
		z->g = (5 * z->i + 1) % 16;
	}
	else if (z->i <= 47)
	{
		z->ff = z->bb ^ z->cc ^ z->dd;
		z->g = (3 * z->i + 5) % 16;
	}
	else if (z->i <= 63)
	{
		z->ff = z->cc ^ (z->bb | (~z->dd));
		z->g = (7 * z->i) % 16;
	}
	z->ff = z->ff + z->aa + g_ks[z->i] + h->arr[z->g + ctr];
	z->aa = z->dd;
	z->dd = z->cc;
	z->cc = z->bb;
	z->bb = z->bb + ((z->ff << g_s[z->i]) | (z->ff >> (32 - g_s[z->i])));
}

void	hash(t_hash *h, t_opt *opt)
{
	t_val			new;
	t_iter			zed;
	unsigned int	ctr;
	size_t			d;

	initv(&new);
	initz(&zed, &new);
	ctr = 0;
	d = 0;
	while (d < h->bytes)
	{
		initz(&zed, &new);
		while (++zed.i < 64)
			whilec(&zed, h, ctr);
		ctr += 16;
		new.a0 += zed.aa;
		new.b0 += zed.bb;
		new.c0 += zed.cc;
		new.d0 += zed.dd;
		d += 64;
	}
	handle_out(new, h, opt);
}
