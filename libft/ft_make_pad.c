/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_pad.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 10:34:54 by efriedma          #+#    #+#             */
/*   Updated: 2018/05/22 17:44:10 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*make_pad(t_data *curr, char *print)
{
	char	*snew;
	char	*tmp;

	tmp = print;
	snew = ft_memalloc(1 + curr->pad - ft_strlen(print));
	if (curr->hash)
		ft_memset(snew, curr->chrfil, (curr->pad - 2) - ft_strlen(print));
	else
		ft_memset(snew, curr->chrfil, curr->pad - ft_strlen(print));
	print = ft_strjoin(snew, print);
	ft_memdel((void**)&tmp);
	ft_memdel((void**)&snew);
	return (print);
}
