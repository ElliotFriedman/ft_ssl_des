/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 16:02:27 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/15 20:42:02 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

int		hashopt(char *argv, t_opt *new, int *on)
{
	int	fin;

	fin = 0;
	if (ft_strchr(argv, (int)'p') && ++fin)
		new->p = 1;
	if (ft_strchr(argv, (int)'q') && ++fin)
		new->q = 1;
	if (ft_strchr(argv, (int)'r') && ++fin)
		new->r = 1;
	if (ft_strchr(argv, (int)'s') && ++fin)
		new->s = 1;
	if ((new->s || new->r || new->q || new->p) && fin)
	{
		new->on = 1;
		*on = 1;
		return (1);
	}
	return (0);
}

int		get_hash_opt(int argc, char **argv, t_opt *new, int i)
{
	int			on;

	on = 1;
	while (i < argc && on && open(argv[i], O_RDONLY) == -1)
	{
		if (argv[i][0] == '-' && hashopt(argv[i], new, &on))
			return (1);
		else
			on = 0;
		i++;
	}
	return (0);
}
