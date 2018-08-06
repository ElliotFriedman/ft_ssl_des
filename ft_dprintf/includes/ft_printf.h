/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 17:40:29 by efriedma          #+#    #+#             */
/*   Updated: 2018/05/25 17:18:39 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <wchar.h>

int					print_binary(t_data *curr, va_list list);
int					print_wchar(t_data *curr, va_list list);
int					print_wstr(t_data *curr, va_list list);
void				ft_nputstr(char *str, t_data *curr, int precise);
char				*new_data(char *print, t_data *curr);
int					empty(t_data *curr);
int					ft_dprintf(int fd, const char *str, ...);
void				find_flags(t_data *curr, const char *str, va_list list);
long long			nint_flags(t_data *curr, va_list list);
unsigned long long	uint_flags(t_data *curr, va_list list);
int					print_char(t_data *curr, va_list list);
int					print_str(t_data *curr, va_list list);
int					print_octal(char c, t_data *curr, va_list list);
int					print_int(t_data *curr, va_list list);
int					print_uint(char c, t_data *curr, va_list list);
int					print_hex(char c, t_data *curr, va_list list);
void				ft_mputstr(char *str, t_data *curr);
int					print_per(t_data *curr);
int					hexgen(char *print, char *snew, t_data *curr);
int					print_addy(t_data *curr, va_list list);

#endif
