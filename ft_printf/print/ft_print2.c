/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 21:03:32 by efriedma          #+#    #+#             */
/*   Updated: 2018/05/22 19:01:10 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int			outgen2(char *print, t_data *curr)
{
	char	*buf;

	if (curr->pad > (int)ft_strlen(print))
	{
		buf = ft_memalloc(curr->pad - ft_strlen(print));
		ft_memset(buf, curr->chrfil, curr->pad - ft_strlen(print));
		if (curr->lr)
		{
			ft_mputstr(print, curr);
			ft_mputstr(buf, curr);
		}
		else
		{
			ft_mputstr(buf, curr);
			ft_mputstr(print, curr);
		}
		ft_memdel((void*)&buf);
		ft_memdel((void*)&print);
	}
	else
	{
		ft_mputstr(print, curr);
		ft_memdel((void*)&print);
	}
	return (1);
}

char		*help(char *tmp, char *print)
{
	tmp = print;
	print = ft_strjoin("0x", print);
	return (print);
}

int			print_per(t_data *curr)
{
	char	*str;

	if (curr->pad)
	{
		str = ft_memalloc(curr->pad);
		ft_memset(str, 32, curr->pad - 1);
	}
	if (!curr->lr)
	{
		ft_mputstr(str, curr);
		ft_putchar('%');
	}
	else
	{
		ft_putchar('%');
		ft_mputstr(str, curr);
	}
	curr->iter++;
	return (1);
}
