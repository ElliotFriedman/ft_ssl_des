/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_addy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 18:59:59 by efriedma          #+#    #+#             */
/*   Updated: 2018/08/04 15:40:44 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*pad(char *print, t_data *curr)
{
	char	*snew;
	int		len;

	if ((int)ft_strlen(print) < curr->pad)
	{
		len = (curr->pad - (int)ft_strlen(print)) + 2;
		snew = ft_memalloc(len);
		ft_memset(snew, curr->chrfil, len - 2);
	}
	else
		snew = 0;
	return (snew);
}

int		print_addy(t_data *curr, va_list list)
{
	char				*tmp;
	char				*snew;
	char				*print;
	unsigned long long	stor;

	ft_strncpy(curr->mod, "ll", 2);
	stor = uint_flags(curr, list);
	if (!stor && curr->precheck && !curr->pad && !curr->precision)
		return (hexgen(ft_strdup("0x"), 0, curr));
	print = ft_uitoabase(stor, 16);
	if (curr->precision > ((int)ft_strlen(print) + 2))
	{
		tmp = print;
		snew = ft_memalloc(curr->precision - (ft_strlen(print + 1)));
		ft_memset(snew, 48, curr->precision - (int)ft_strlen(print));
		print = ft_strjoin(snew, print);
		ft_memdel((void*)&tmp);
		ft_memdel((void*)&snew);
	}
	tmp = print;
	print = ft_strjoin("0x", print);
	ft_memdel((void*)&tmp);
	snew = pad(print, curr);
	return (hexgen(print, snew, curr));
}

int		print_binary(t_data *cur, va_list list)
{
	unsigned long long	nbr;
	char				*print;
	char				*buf;

	ft_strncpy(cur->mod, "ll", 2);
	nbr = uint_flags(cur, list);
	buf = 0;
	print = ft_uitoabase(nbr, 2);
	if (cur->precision > (int)ft_strlen(print))
		print = make_pre(cur, print);
	if (cur->pad > (int)ft_strlen(print))
		buf = ft_malset(cur->pad - ft_strlen(print), cur->chrfil);
	if (cur->plus && !cur->negative)
		print = prep_x(print, "+");
	if (cur->negative)
		print = prep_x(print, "-");
	if (cur->chk && !cur->lr)
		ft_mputstr(" ", cur);
	return (hexgen(print, buf, cur));
}
