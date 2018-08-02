/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 16:21:59 by efriedma          #+#    #+#             */
/*   Updated: 2018/08/01 15:49:11 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

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
	return (hold);
}
