/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 12:57:59 by efriedma          #+#    #+#             */
/*   Updated: 2018/05/22 18:43:54 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

long long			nint_flags(t_data *curr, va_list list)
{
	if (curr->mod[0] == 'l' && curr->mod[1] == 'l')
		return (va_arg(list, long long));
	else if (curr->mod[0] == 'l')
		return ((long long)va_arg(list, long int));
	else if (curr->mod[0] == 'h' && curr->mod[1] == 'h')
		return ((char)va_arg(list, int));
	else if (curr->mod[0] == 'h')
		return ((short)va_arg(list, int));
	else if (curr->mod[0] == 'j')
		return (va_arg(list, long long));
	else if (curr->mod[0] == 'z')
		return ((long long)va_arg(list, size_t));
	return ((long long)va_arg(list, int));
}

unsigned long long	uint_flags(t_data *curr, va_list list)
{
	if (curr->mod[0] == 'l' && curr->mod[1] == 'l')
		return (va_arg(list, unsigned long long));
	else if (curr->mod[0] == 'l')
		return ((unsigned long long)va_arg(list, unsigned long));
	else if (curr->mod[0] == 'h' && curr->mod[1] == 'h')
		return ((unsigned char)va_arg(list, unsigned int));
	else if (curr->mod[0] == 'h')
		return ((unsigned short int)va_arg(list, unsigned int));
	else if (curr->mod[0] == 'j')
		return ((unsigned long long)va_arg(list, unsigned long long));
	else if (curr->mod[0] == 'z')
		return ((unsigned long long)va_arg(list, size_t));
	return (va_arg(list, unsigned int));
}
