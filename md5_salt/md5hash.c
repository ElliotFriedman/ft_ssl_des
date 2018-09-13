/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 19:18:29 by efriedma          #+#    #+#             */
/*   Updated: 2018/09/12 23:30:00 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

const unsigned int g_ks[64];

const int g_s[64];

unsigned long long	*handle_pass(t_val new)
{
	unsigned long long	*ret;

	//turn the output into an array of 2 unsigned long longs
	//this will be our salt
	ret = ft_memalloc(sizeof(unsigned long long) * 2);
	//00000000 00000000 00000000 00000000 | 11111111 11111111 11111111 11111111
	ret[0] = new.b0;
	ret[0] <<= 32;
	//11111111 11111111 11111111 11111111 | 00000000 00000000 00000000 00000000
	ret[0] += new.a0;
	//11111111 11111111 11111111 11111111 | 11111111 11111111 11111111 11111111
	ret[1] = new.d0;
	ret[1] <<= 32;
	ret[1] += new.c0;
	return (ret);
}

void	init_v(t_val *new)
{
	new->a0 = 0x67452301;
	new->b0 = 0xefcdab89;
	new->c0 = 0x98badcfe;
	new->d0 = 0x10325476;
}

void	init_z(t_iter *z, t_val *new)
{
	z->aa = new->a0;
	z->bb = new->b0;
	z->cc = new->c0;
	z->dd = new->d0;
	z->i = -1;
}

void	whilesalt(t_iter *z, t_hash *h, size_t ctr)
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

unsigned long long	*hash_pass(t_hash *h)
{
	t_val			new;
	t_iter			zed;
	unsigned int	ctr;
	size_t			d;

	init_v(&new);
	init_z(&zed, &new);
	ctr = 0;
	d = 0;
	while (d < h->bytes)
	{
		init_z(&zed, &new);
		while (++zed.i < 64)
			whilesalt(&zed, h, ctr);
		ctr += 16;
		new.a0 += zed.aa;
		new.b0 += zed.bb;
		new.c0 += zed.cc;
		new.d0 += zed.dd;
		d += 64;
	}
	return (handle_pass(new));
}
