/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 16:21:59 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/15 17:01:17 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

unsigned long long	g_iv;
extern size_t		g_ivbool;
extern size_t		g_strlen;

unsigned long long	*passhash(t_hash *h)
{
	if (g_strlen)
		h->bytes = ft_strlen(h->data);
	h->ini = h->bytes;
	epad(h);
	h->arr = (unsigned int *)h->data;
	return (hash_pass(h));
}

unsigned long long	*create_key(t_hash *h)
{
	t_opt				*s;
	int					file;
	unsigned long long	*hold;

	init_a_des(&h, &s, &file);
	hold = passhash(h);
	rev_8byte((char*)hold, 16);
	if (!g_ivbool)
		g_iv = hold[1];
	free(h->data);
	fstruct(s, h);
	return (hold);
}
