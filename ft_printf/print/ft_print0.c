/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 21:40:30 by efriedma          #+#    #+#             */
/*   Updated: 2018/05/24 23:57:40 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		hexgen2(char *print, char *snew, t_data *curr)
{
	if (curr->lr && snew)
	{
		ft_mputstr(print, curr);
		ft_mputstr(snew, curr);
		ft_memdel((void*)&print);
		ft_memdel((void*)&snew);
	}
	else if (snew)
	{
		ft_mputstr(snew, curr);
		ft_mputstr(print, curr);
		ft_memdel((void*)&print);
		ft_memdel((void*)&snew);
	}
	else
	{
		ft_mputstr(print, curr);
		ft_memdel((void*)&print);
	}
	return (1);
}

void	chk_flag(char c, t_data *cu)
{
	if (c == 'O')
		ft_strncpy(cu->mod, "ll", 2);
}

int		print_octal(char c, t_data *cu, va_list list)
{
	char				*print;
	char				*snew;
	unsigned long long	stor;
	int					i;

	i = 0;
	snew = 0;
	chk_flag(c, cu);
	stor = uint_flags(cu, list);
	if (cu->lr && cu->chrfil == 48)
		cu->chrfil = 32;
	if (!cu->precision && cu->precheck && !stor && !cu->pad && !cu->hash)
		return (1);
	if (!cu->precision && cu->precheck && !stor && cu->pad && !cu->hash)
		return (hexgen2(new_data("", cu), 0, cu));
	print = ft_uitoabase(stor, 8);
	if ((cu->hash) && stor)
		print = prep_x(print, "0");
	if (cu->precheck && cu->precision > (int)ft_strlen(print))
		print = make_pre(cu, print);
	if ((int)ft_strlen(print) < cu->pad && cu->chrfil == 48)
		print = make_pad(cu, print);
	if ((int)ft_strlen(print) < cu->pad && cu->chrfil != 48)
		snew = new_data(print, cu);
	return (hexgen2(print, snew, cu));
}
