/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 17:04:26 by efriedma          #+#    #+#             */
/*   Updated: 2018/06/27 23:58:32 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

int				s256hash(char *hash1, t_hash *h, t_opt *s)
{
	if (!hash1)
	{
		ft_printf("Error!\n");
		exit(0);
	}
	h->data = ft_strdup(hash1);
	h->name = hash1;
	h->bytes = ft_strlen(h->data);
	h->ini = h->bytes;
	epad(h);
	h->arr = (unsigned int *)h->data;
	swap(h);
	sha256hash(h, s);
	ft_memdel((void**)&h->data);
	if (h->pipe)
		ft_memdel((void**)&h->name);
	h->pipe = 0;
	return (1);
}

int				f256hash(char *hash1, t_hash *h, t_opt *s, int *file)
{
	*file += 1;
	if (!ft_fread(hash1, h))
		return (0);
	h->name = hash1;
	epad(h);
	h->arr = (unsigned int *)h->data;
	swap(h);
	sha256hash(h, s);
	ft_memdel((void**)&h->data);
	return (1);
}

void			sha256start(char **argv, int argc)
{
	t_hash	*h;
	t_opt	*s;
	int		file;

	s = ft_memalloc(sizeof(t_opt));
	h = ft_memalloc(sizeof(t_hash));
	h->i = get_opt_loop(2, argc, argv, s);
	if (!do_one(s, h, &file) && (((int)h->i == argc) && (s->p || rstdin(h))))
		s256hash(h->data, h, s);
	else if (!one_two(argc, s, h) && (argc == (int)h->i && rstdin(h)))
		set_n_run(h, s);
	while ((int)h->i < argc)
	{
		while (!file && get_opt(argc, argv, s, h->i) && (int)h->i < argc)
			h->i++;
		if (!file && s->on && s->s)
			s256hash(argv[h->i], h, s);
		else if (!f256hash(argv[h->i], h, s, &file))
			p1(argv, h);
		else if (!file && ((int)h->i == argc && rstdin(h)))
			s256hash(h->data, h, s);
		zer0h(s, h);
		h->i++;
	}
	ffstruct(s, h);
}
