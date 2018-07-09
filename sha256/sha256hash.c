/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256hash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 23:35:29 by efriedma          #+#    #+#             */
/*   Updated: 2018/06/27 22:37:13 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

unsigned int g_k[64] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
	0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa,
	0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138,
	0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624,
	0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f,
	0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

void			cmpct(t_sha *n)
{
	n->a = n->h0;
	n->b = n->h1;
	n->c = n->h2;
	n->d = n->h3;
	n->e = n->h4;
	n->f = n->h5;
	n->g = n->h6;
	n->h = n->h7;
}

void			cmpct1(t_sha *n)
{
	n->h0 += n->a;
	n->h1 += n->b;
	n->h2 += n->c;
	n->h3 += n->d;
	n->h4 += n->e;
	n->h5 += n->f;
	n->h6 += n->g;
	n->h7 += n->h;
}

void			while1(t_sha *n, size_t *i, unsigned int *w)
{
	n->s0 = (RR(w[*i - 15], 7)) ^ (RR(w[*i - 15], 18)) ^ (w[*i - 15] >> 3);
	n->s1 = (RR(w[*i - 2], 17)) ^ (RR(w[*i - 2], 19)) ^ (w[*i - 2] >> 10);
	w[*i] = w[*i - 16] + n->s0 + w[*i - 7] + n->s1;
	*i += 1;
}

void			sha256hash(t_hash *hs, t_opt *nopt)
{
	t_sha			n;
	size_t			ctr;
	size_t			i;
	unsigned int	*w;
	size_t			x;

	t_sha_init(&n, &w);
	x = 0;
	ctr = 0;
	while (ctr < hs->bytes)
	{
		ft_memcpy(w, (void*)&hs->arr[x], 64);
		i = 16;
		while (i < 64)
			while1(&n, &i, w);
		i = -1;
		cmpct(&n);
		while (++i < 64)
			whiled(&n, i, w);
		cmpct1(&n);
		x += 16;
		ctr += 64;
	}
	ft_memdel((void*)&w);
	handle_out1(&n, hs, nopt);
}
