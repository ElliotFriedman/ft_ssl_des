/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 16:21:59 by efriedma          #+#    #+#             */
/*   Updated: 2018/09/18 00:37:14 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

unsigned long long   g_iv;

unsigned long long	*passhash(char *str, t_hash *h)
{
	h->data = str;
	h->bytes = ft_strlen(h->data);
	h->ini = h->bytes;
	epad(h);
	h->arr = (unsigned int *)h->data;
	return (hash_pass(h));
}

unsigned long long	*create_key(char *str)
{
	t_hash				*h;
	//dont delete this so that we can use old ported functions
	//and change as little as possible
	t_opt				*s;
	int					file;
	unsigned long long	*hold;

	init_a(&h, &s, &file);
	//strdup so that when we free in epad we don't free stack mem
	hold = passhash(ft_strdup(str), h);
	fstruct(s, h);
	rev_8byte((char*)hold, 16);
	//Delete this line in the future, this is only to avoid compiler errors
	//str[0] = 0;
	
	//unsigned long long	*tmp = ft_memalloc(16);
	//tmp[0] = 1383827165325090801;

	//ft_printf("key             = %064b\n", tmp[0]);
	//return tmp;
//	printf("key: %016llX\n", hold[0]);
//		//	printf("%016llu\n", hold[0]);
	g_iv = hold[1];
	printf("iv: %016llX\n", g_iv);

	return (hold);
}
