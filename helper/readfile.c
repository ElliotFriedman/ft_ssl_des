/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 21:51:40 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/09 01:07:24 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

size_t	ft_flen(int fd)
{
	size_t	i;
	size_t	ctr;
	char	buf[100];

	ctr = 0;
	i = 0;
	while ((i = read(fd, buf, 100)) > 0)
		ctr += i;
	close(fd);
	return (ctr);
}

int		ft_fread(char *str, t_hash *h)
{
	int		fd;
	size_t	asize;
	char	*afile;
	size_t	chk;

	chk = 0;
	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (0);
	else
	{
		h->fd = 1;
		asize = ft_flen(fd);
		afile = ft_strnew(asize);
		fd = open(str, O_RDONLY);
		chk = read(fd, afile, asize);
		h->data = ft_memjoin(h->data, afile, h->bytes, chk);
		h->ini = asize + h->bytes;
		h->bytes += chk;
		close(fd);
		h->arr = (unsigned int *)h->data;
		free(afile);
		return (1);
	}
	return (0);
}

int		rkey(t_hash *h)
{
	char	*buf;
	char	*str;
	char	*tmp;

	str = ft_strnew(0);
	h->bytes = 0;
	buf = ft_memalloc(2);
	while (read(0, buf, 1) == 1)
	{
		tmp = str;
		str = ft_memjoin(str, buf, h->bytes, 1);
		h->bytes++;
		free(tmp);
	}
	str[h->bytes] = 0;
	ft_memdel((void**)&buf);
	h->data = str;
	h->ini = h->bytes;
	h->pipe = 1;
	return (1);
}

int		rstdin(t_hash *h)
{
	char	buf[2];
	char	*str;
	char	*tmp;

	str = 0;
	h->bytes = 0;
	buf[1] = 0;
	if (!isatty(0))
	{
		str = ft_strnew(0);
		while (read(0, buf, 1) == 1)
		{
			tmp = str;
			str = ft_memjoin(str, buf, h->bytes, 1);
			h->bytes++;
			free(tmp);
		}
		h->data = str;
		h->pipe = 1;
	}
	h->ini = h->bytes;
	return (h->bytes);
}
