/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 14:42:19 by efriedma          #+#    #+#             */
/*   Updated: 2018/08/05 22:49:32 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		_find(char c, va_list list, t_data *curr)
{
	if (c == 'O' || c == 'o')
		return (print_octal(c, curr, list));
	else if (c == 'U' || c == 'u')
		return (print_uint(c, curr, list));
	else if (c == 'd' || c == 'i' || c == 'D')
	{
		if (c == 'D')
			ft_strncpy(curr->mod, "l", 1);
		return (print_int(curr, list));
	}
	else if (c == 'c' && curr->mod[0] != 'l')
		return (print_char(curr, list));
	else if (c == 'C' || (c == 'c' && curr->mod[0] == 'l'))
		return (print_wchar(curr, list));
	else if (c == 's' && curr->mod[0] != 'l')
		return (print_str(curr, list));
	else if (c == 'S' || (c == 's' && curr->mod[0] == 'l'))
		return (print_wstr(curr, list));
	else if (c == 'x' || c == 'X')
		return (print_hex(c, curr, list));
	else if (c == 'p')
		return (print_addy(curr, list));
	return (0);
}

int		_exception(const char *str, int *i)
{
	if ((ft_strlen(str) > 1) && (str[0] == '%' && str[1] == '%'))
	{
		*i += 1;
		return (1);
	}
	else
		return (0);
}

int		_ft_putstr_until(const char *str, t_data *curr)
{
	int i;
	int flag;
	int x;

	x = 0;
	flag = 0;
	i = 0;
	if (str[0] == '%' && !(_exception(str, &x)))
	{
		curr->sum++;
		return (1);
	}
	while ((str[i] && str[i] != '%') || (_exception(&str[i], &i)))
	{
		curr->iter++;
		write(curr->fd, &str[i], 1);
		i++;
	}
	curr->sum += i;
	if (str[i] == 0)
		return (0);
	return (i);
}

int		_dispatch(va_list list, const char *str, int fd)
{
	t_data	*curr;
	int		tmp;

	curr = ft_memalloc(sizeof(t_data));
	curr->fd = fd;
	while ((tmp = _ft_putstr_until(&str[curr->sum], curr)))
	{
		find_flags(curr, &str[curr->sum], list);
		while ((str[curr->sum])
				&& !(_find(str[curr->sum], list, curr)))
		{
			curr->sum++;
			if (str[curr->sum] == '%')
				print_per(curr);
		}
		if (curr->sum == (int)ft_strlen(str))
			break ;
		curr->sum++;
		init(curr);
	}
	tmp = curr->iter;
	free(curr);
	va_end(list);
	return (tmp);
}

int		ft_dprintf(int fd, const char *str, ...)
{
	int		tmp;
	va_list	list;

	if (fd < 0)
	{
		ft_putstr("File descriptor invalid\n");
		return (0);
	}
	va_start(list, str);
	tmp = _dispatch(list, str, fd);
	return (tmp);
}
