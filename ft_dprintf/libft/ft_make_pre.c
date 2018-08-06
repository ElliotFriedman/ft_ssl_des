/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_pre.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 10:36:48 by efriedma          #+#    #+#             */
/*   Updated: 2018/05/22 10:36:56 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*make_pre(t_data *curr, char *print)
{
	char	*tmp;
	char	*snew;

	tmp = print;
	snew = ft_memalloc(curr->precision - ft_strlen(print) + 1);
	ft_memset(snew, 48, curr->precision - ft_strlen(print));
	print = ft_strjoin(snew, print);
	ft_memdel((void**)&snew);
	ft_memdel((void**)&tmp);
	return (print);
}
