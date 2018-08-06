/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 21:46:02 by efriedma          #+#    #+#             */
/*   Updated: 2018/05/24 14:56:39 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	find_mod(t_data *curr, const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == 'l' && ++i)
		curr->mod[i - 1] = 'l';
	while (str[i] && str[i] == 'h' && ++i)
		curr->mod[i - 1] = 'h';
	if (str[i] && str[i] == 'j' && ++i)
		curr->mod[i - 1] = 'j';
	if (str[i] && str[i] == 'z' && ++i)
		curr->mod[i - 1] = 'z';
	if (curr->plus && curr->chk)
		curr->chk = 0;
}

void	chk(va_list list, int *i)
{
	va_arg(list, int);
	*i += 1;
}

void	find_width_precision(t_data *curr, const char *str, va_list list)
{
	int	i;

	i = 0;
	curr->pad = ft_matoi(str);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i] && str[i] != '.' && str[i] != 'l' && str[i] != 'h'
			&& str[i] != 'z' && str[i] != 'U' && str[i] != 'u' && str[i] != 'b'
			&& str[i] != 'j' && str[i] != 'd' && str[i] != 'D' && str[i] != 'i'
			&& str[i] != 'o' && str[i] != 'O' && str[i] != 'x' && str[i] != 'X'
			&& str[i] != 'p' && str[i] != 's' && str[i] != 'S' && str[i] != 'c')
		str[i] == '*' ? chk(list, &i) : i++;
	if (str[i] && str[i] == '.')
	{
		i++;
		str[i] == '*' ? chk(list, &i) : (i += (0));
		curr->precision = ft_matoi(&str[i]);
		curr->precheck = 1;
		while (str[i] && ft_isdigit(str[i]))
			i++;
	}
	find_mod(curr, &str[i]);
}

void	find_flags(t_data *curr, const char *str, va_list list)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '.' && str[i] != 'u' && str[i] != 'U'
			&& str[i] != 'j' && str[i] != 'd' && str[i] != 'D' && str[i] != 'i'
			&& str[i] != 'o' && str[i] != 'O' && str[i] != 'x' && str[i] != 'X'
			&& str[i] != 'p' && str[i] != 's' && str[i] != 'S' && str[i] != 'c'
			&& str[i] != 'b' && !(str[i] >= '1' && str[i] <= '9'))
	{
		if (str[i] == '#')
			curr->hash = 1;
		if (str[i] == '0')
			curr->chrfil = 48;
		if (str[i] == '-')
			curr->lr = 1;
		if (str[i] == '+')
			curr->plus = 1;
		if (str[i] == ' ' && ((curr->chk = 1)))
			curr->chrfil = 32;
		i++;
	}
	if (curr->chrfil != 48)
		curr->chrfil = 32;
	find_width_precision(curr, str, list);
}
