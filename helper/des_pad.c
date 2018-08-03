/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_pad.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 18:02:38 by efriedma          #+#    #+#             */
/*   Updated: 2018/08/02 18:47:16 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

char		*add_byte(char *data, size_t bytes)
{
	char	*snew;
	char	*tmp;

	tmp = data;
	bytes++;
	snew = ft_memalloc(bytes);
	ft_memcpy(snew, data, bytes - 1);
	free(tmp);
	return (snew);
}

int		des_pad(char **encrypt, size_t len)
{
	size_t	dif;
	char	*set;

	dif = len % 8;
	ft_printf("dif: %d\n", dif);
	*set = 8 - dif;
	if (dif == 0)
		*set = 8;
	dif = *set;
	while (dif)
	{
		len++;
		*encrypt = add_byte(*encrypt, len);
		ft_memset(&*encrypt[len], set, 1);
		dif--;
	}
	return (len);
}

void	print_bytes(char *str, int len)
{
	size_t	i = 0;
	
	while (i < len)
	{
		ft_printf("%02x ", str[i]);
		i++;
	}
	ft_putstr("\n");
}

int main(void)
{
	char *a = malloc(6);
	ft_strcpy(a, "Pad me");
	print_bytes(a, 6);
	des_pad(&a, 6);
	print_bytes(a, 8);

	return 1;
}
