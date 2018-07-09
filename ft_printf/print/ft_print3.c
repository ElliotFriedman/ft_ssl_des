/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:26:40 by efriedma          #+#    #+#             */
/*   Updated: 2018/06/05 11:39:29 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		hexgen(char *print, char *snew, t_data *curr)
{
	if (curr->lr && snew)
	{
		ft_mputstr(print, curr);
		ft_mputstr(snew, curr);
		free(snew);
	}
	else if (snew)
	{
		ft_mputstr(snew, curr);
		ft_mputstr(print, curr);
		free(snew);
	}
	else
		ft_mputstr(print, curr);
	free(print);
	return (1);
}

int		empty(t_data *curr)
{
	char	*snew;
	int		x;

	if (curr->precision > curr->pad)
		x = curr->precision;
	else
		x = curr->pad;
	snew = ft_memalloc(x + 1);
	ft_memset(snew, curr->chrfil, x);
	hexgen(snew, 0, curr);
	return (1);
}

char	*new_data(char *print, t_data *curr)
{
	char	*snew;

	snew = ft_memalloc(1 + curr->pad - ft_strlen(print));
	ft_memset(snew, curr->chrfil, curr->pad - ft_strlen(print));
	return (snew);
}

int		print_hex(char c, t_data *curr, va_list list)
{
	char				*snew;
	char				*print;
	unsigned long long	stor;

	snew = 0;
	stor = uint_flags(curr, list);
	if (curr->chrfil == 48 && curr->lr)
		curr->chrfil = 32;
	if (!curr->precision && curr->precheck && !stor && !curr->pad)
		return (1);
	if ((curr->precheck || curr->pad) && !stor)
		return (empty(curr));
	print = ft_uitoabase(stor, 16);
	if (curr->precheck && curr->precision > (int)ft_strlen(print))
		print = make_pre(curr, print);
	if ((int)ft_strlen(print) < curr->pad && curr->chrfil == 48)
		print = make_pad(curr, print);
	if (curr->hash && stor)
		print = prep_x(print, "0x");
	if ((int)ft_strlen(print) < curr->pad && curr->chrfil != 48)
		snew = new_data(print, curr);
	if (c == 'X')
		print = upper(print);
	return (hexgen(print, snew, curr));
}
