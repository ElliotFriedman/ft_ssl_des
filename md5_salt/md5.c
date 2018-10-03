/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 16:21:59 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/02 20:01:33 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

unsigned long long	g_iv;
extern size_t		g_ivBool;
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
	//pass this in instead of a string, and voilla
	//t_hash				*h;
	//dont delete this so that we can use old ported functions
	//and change as little as possible
	t_opt				*s;
	int					file;
	unsigned long long	*hold;

	init_a_des(&h, &s, &file);
	//strdup so that when we free in epad we don't free stack mem
	//we strdup'ed before we got here :)
	hold = passhash(h);
		//reverse endiannes
	rev_8byte((char*)hold, 16);
	//Delete this line in the future, this is only to avoid compiler errors
	//str[0] = 0;
	//unsigned long long	*tmp = ft_memalloc(16);
	//tmp[0] = 1383827165325090801;
	//ft_printf("key             = %064b\n", tmp[0]);
	//return tmp;
//	printf("key: %016llX\n", hold[0]);
//	ft_printf("password: %s\n", h->data);
//		//	printf("%016llu\n", hold[0]);
	if (!g_ivBool)
		g_iv = hold[1];

	//	else //if (g_decrypt)
//	printf("iv supplied in cl arg: %llx\n", g_iv);
//	printf("iv: %016llX\n", g_iv);
	fstruct(s, h);
	return (hold);
}
