/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 23:22:38 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/08 23:38:55 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

void	printcommands(char *str)
{
	ft_printf("ft_ssl: Error: '%s' is an invalid command.\n", str);
	ft_printf("\nStandard commands:\n\nMessage Digest commands:\nmd5");
	ft_putstr("\nsha256\n\n");
	ft_putstr("Cipher commands:\nbase64\ndes\ndes-ecb\ndes-cbc\n\n");
}
