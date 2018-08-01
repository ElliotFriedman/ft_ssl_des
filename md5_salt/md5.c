/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 16:21:59 by efriedma          #+#    #+#             */
/*   Updated: 2018/07/31 18:03:23 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

int		shash(char *hash1, t_hash *h, t_opt *new)
{
	if (new->p && hash1 && h->pipe)
		ft_printf("%s", h->data);
	if (!hash1)
		return (0);
	if (!h->pipe)
		h->data = ft_strdup(hash1);
	h->name = hash1;
	if (h->data)
		h->bytes = ft_strlen(h->data);
	h->ini = h->bytes;
	epad(h);
	h->arr = (unsigned int *)h->data;
	hash(h, new);
	ft_memdel((void**)&h->data);
	h->pipe = 0;
	return (1);
}


int		zeroh(t_opt *h, t_hash *hash)
{
	hash->pipe = 0;
	h->s = 0;
	return (1);
}

char	*create_salt(char *str)
{
	t_hash		*h;
	t_opt		*s;
	int			file;

	init_a(&h, &s, &file);
	zero
	fstruct(s, h);
}
