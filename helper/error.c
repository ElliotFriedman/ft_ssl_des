/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 23:22:38 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/10 01:42:53 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

extern int	g_ka;
extern int	g_b64;

void	printcommands(char *str)
{
	ft_printf("ft_ssl: Error: '%s' is an invalid command.\n", str);
	ft_printf("\nStandard commands:\n\nMessage Digest commands:\nmd5");
	ft_putstr("\nsha256\n\n");
	ft_putstr("Cipher commands:\nbase64\ndes\ndes-ecb\ndes-cbc\n\n");
}

void	freetmp(unsigned long long *tmp)
{
	if (g_ka != 99999999)
		free(tmp);
}

void	iverror(void)
{
	ft_putstr("Error, no iv specified\n");
	exit(0);
}

void	choice01(unsigned char *h, t_hash *stor)
{
	rkey(stor);
	removewhitespace(stor->data);
	h = (unsigned char *)stor->data;
	h = base64_decode((unsigned char*)stor->data, ft_strlen((char*)h));
	write(1, (char*)h, g_b64);
	free(h);
}

void	err0rr(char error)
{
	ft_printf("base64: option requires an argument -- %c\n", error);
	ft_putstr("Usage:	base64 [-hvD] [-b num] [-i in_file] [-o out_file]\n");
	ft_putstr("	-d, --decode   decodes input\n  -i, --input    input file ");
	ft_putstr("(default: stdin)\n  -o, --output   output file");
	ft_putstr(" (default: stdout)\n");
	exit(0);
}
