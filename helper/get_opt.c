/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 16:02:27 by efriedma          #+#    #+#             */
/*   Updated: 2018/09/12 00:16:19 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

extern int		g_file;
extern int		g_bool;
extern int		g_fd;
extern int		g_decrypt;

int		opt(char *argv, t_opt *new, int i)
{
	g_bool = 0;
	if (ft_strchr(argv, (int)'p') && ++g_bool)
		new->p = 1;
	if (ft_strchr(argv, (int)'q') && ++g_bool)
		new->q = 1;
	if (ft_strchr(argv, (int)'r') && ++g_bool)
		new->r = 1;
	if (ft_strchr(argv, (int)'s') && ++g_bool)
		new->s = 1;
	if ((ft_strchr(argv, (int)'D') || ft_strchr(argv, (int)'d')) && ++g_bool && ++g_decrypt)
		new->d = 1;
	if (ft_strchr(argv, (int)'a') && ++g_bool)
		new->a = 1;
	if (ft_strchr(argv, (int)'o') && ++g_bool)
	{
		ft_printf("-o flag found at argc %d\n", i);
		new->o = 1;
		g_file = ++i;
	}
	if (g_bool)//(new->d || new->s || new->r || new->q || new->p) && fin)
	{
		new->on = 1;
		//*on = 1;
		return (1);
	}
	return (0);
}

int		get_opt(int argc, char **argv, t_opt *new, int i)
{
	int			fd;

	fd = 0;
	while (i < argc )/*&& on*/// && open(argv[i], O_RDONLY) == -1)
	{
		if (argv[i][0] == '-' && (open(argv[i], O_RDONLY) == -1) && opt(argv[i], new, i))
			return (1);
		else if (!g_fd && new->o && ((fd = (open(argv[i], O_RDONLY)) > 2)))
		{
			ft_printf("found file descriptor %d with name %s found at index %d\n", fd, argv[i],i);
			g_fd = fd;
		}
		i++;
	}
	return (0);
}
