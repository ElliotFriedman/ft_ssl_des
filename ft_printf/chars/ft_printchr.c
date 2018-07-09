/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 21:20:23 by efriedma          #+#    #+#             */
/*   Updated: 2018/05/23 14:26:20 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		print_char(t_data *curr, va_list list)
{
	char	*str;

	if (!curr->pad)
		ft_putchar(va_arg(list, int));
	else
	{
		str = ft_memalloc(curr->pad + 1);
		ft_memset(str, curr->chrfil, curr->pad - 1);
		if (curr->lr)
		{
			ft_putchar(va_arg(list, int));
			ft_mputstr(str, curr);
		}
		else
		{
			ft_mputstr(str, curr);
			ft_putchar(va_arg(list, int));
		}
		ft_memdel((void*)&str);
	}
	curr->iter++;
	return (1);
}

void	ft_prints(t_data *curr)
{
	if (curr->chrfil == 32)
		while (curr->pad > 0)
		{
			ft_mputstr(" ", curr);
			curr->pad--;
		}
	else
	{
		while (curr->pad > 0)
		{
			ft_mputstr("0", curr);
			curr->pad--;
		}
	}
}

void	handle_output(t_data *curr, char *print)
{
	if (curr->lr)
	{
		ft_mputstr(print, curr);
		ft_prints(curr);
	}
	else
	{
		ft_prints(curr);
		ft_mputstr(print, curr);
	}
	ft_memdel((void*)&print);
}

int		handle_pre(t_data *curr, char *str)
{
	if (curr->lr && curr->precheck)
	{
		ft_nputstr(str, curr, curr->precision);
		ft_prints(curr);
		ft_memdel((void**)&str);
		return (1);
	}
	else if (!curr->lr && curr->precheck)
	{
		ft_prints(curr);
		ft_nputstr(str, curr, curr->precision);
		ft_memdel((void**)&str);
		return (1);
	}
	return (0);
}

int		print_str(t_data *curr, va_list list)
{
	char *str;

	str = va_arg(list, char*);
	if (str)
		str = ft_strdup(str);
	if (!str)
		str = ft_strdup("(null)");
	if (!curr->precheck)
		curr->pad -= (int)ft_strlen(str);
	else
	{
		if ((int)ft_strlen(str) > curr->precision)
			curr->pad -= curr->precision;
		else
			curr->pad -= (int)ft_strlen(str);
	}
	if (handle_pre(curr, str))
		return (1);
	else if ((!curr->lr && !curr->precheck) || (curr->lr && !curr->precheck))
		handle_output(curr, str);
	return (1);
}
