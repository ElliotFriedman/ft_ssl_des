/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 16:21:59 by efriedma          #+#    #+#             */
/*   Updated: 2018/08/01 15:33:53 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

unsigned long long	*shash(t_hash *h)
{
	if (h->data)
		h->bytes = ft_strlen(h->data);
	h->ini = h->bytes;
	epad(h);
	h->arr = (unsigned int *)h->data;
	return (hash(h, new));
}


int					zeroh(t_opt *h, t_hash *hash)
{
	hash->pipe = 0;
	h->s = 0;
	return (1);
}

unsigned long long	*create_salt(char *str)
{
	t_hash				*h;
	//dont delete this so that we can use old ported functions
	//and change as little as possible
	t_opt				*s;
	int					file;
	unsigned long long	*hold;

	init_a(&h, &s, &file);
	hold = shash(h, 
	fstruct(s, h);
	return (
}
