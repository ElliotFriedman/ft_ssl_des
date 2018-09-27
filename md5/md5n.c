/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5n.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 23:41:46 by efriedma          #+#    #+#             */
/*   Updated: 2018/09/26 22:05:47 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

void	error(void)
{
	ft_printf("md5: option requires an argument -- s\n");
	ft_printf("usage: md5 [-pqrtx] [-s string] [files ...]\n");
	exit(0);
}

int		fstruct(t_opt *opt, t_hash *h)
{
	ft_memdel((void**)&h);
	ft_memdel((void**)&opt);
	return (1);
}

void	init_a_des(t_hash **h, t_opt **s, int *file)
{
	*file = 0;
	*s = ft_memalloc(sizeof(t_opt));
	h[0]->i = 2;
}

void	init_a(t_hash **h, t_opt **s, int *file)
{
	*file = 0;
	*s = ft_memalloc(sizeof(t_opt));
	*h = ft_memalloc(sizeof(t_hash));
	h[0]->i = 2;
}

size_t	get_opt_loopb(size_t i, int a, char **av, t_opt *s)
{
	while (get_opt(a, av, s, i))
		i++;
	return (i);
}

int		seta(t_hash *h, t_opt *s)
{
	h->pipe = 1;
	s->p = 1;
	return (1);
}
