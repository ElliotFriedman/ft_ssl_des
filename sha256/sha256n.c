/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256n.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 23:48:01 by efriedma          #+#    #+#             */
/*   Updated: 2018/06/27 23:48:40 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

size_t			get_opt_loop(size_t i, int argc, char **argv, t_opt *s)
{
	while (get_opt(argc, argv, s, i))
		i++;
	return (i);
}

int				do_one(t_opt *s, t_hash *h, int *file)
{
	*file = 0;
	h->sha = 1;
	if (h->i != 2 && rstdin(h))
	{
		s256hash(h->data, h, s);
		return (1);
	}
	return (0);
}

int				one_two(int argc, t_opt *s, t_hash *h)
{
	if (argc == (int)h->i && rkey(h))
	{
		s->q = 1;
		s256hash(h->data, h, s);
		zer0h(s, h);
		return (1);
	}
	return (0);
}

void			set_n_run(t_hash *h, t_opt *s)
{
	h->pipe = 1;
	s->p = 1;
	s256hash(h->data, h, s);
}

void			p1(char **argv, t_hash *h)
{
	ft_printf("ft_ssl: md5: %s: No such file or directory\n", argv[h->i]);
}
