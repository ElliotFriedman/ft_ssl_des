/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_salt_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 22:20:20 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/15 16:58:59 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

extern unsigned long long	g_salt;
extern char					*g_saltchars;
extern int					g_saltcharbool;

void						handle_salt_add(t_hash *h)
{
	char					*ftmp;

	ftmp = h->data;
	h->data = ft_memjoin(h->data, &g_salt, h->bytes, 8);
	h->bytes += 8;
	free(ftmp);
}

void						create_salt(t_hash *h, char *salt)
{
	g_saltchars = getsalt(h, salt);
	g_saltcharbool = 1;
}
