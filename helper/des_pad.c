/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_pad.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 18:02:38 by efriedma          #+#    #+#             */
/*   Updated: 2018/08/02 19:33:48 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

void    print_bytes(char *str, int len);

char		*add_byte(char *data, size_t bytes)
{
	char	*snew;
	char	*tmp;

	//this will be freed after we re assign data
	tmp = data;
	bytes++;
	//add an extra byte
	snew = ft_memalloc(bytes);
	//copy the old bytes in from data
	ft_memcpy(snew, data, bytes - 1);
	//free the old data
	free(tmp);
	//return the new data
	return (snew);
}

char	*des_pad(char *encrypt, size_t len)
{
	size_t	dif;
	char	set[1];

	dif = len % 8;
	ft_printf("dif: %d\n", dif);
	set[0] = 8 - dif;
	if (dif == 0)
		set[0] = 8;
	dif = set[0];
	ft_printf("adding %d bytes\n", dif);
	while (dif)
	{
		ft_printf("Dif in while loop %d, Len: %d\n", dif, len + 1);
		len++;
		encrypt = add_byte(encrypt, len);

		ft_memset(&encrypt[len - 1], (int)set[0], 1);
		print_bytes(encrypt, len);
		dif--;
	}
	ft_printf("total len %d\n", len);
	return (encrypt);
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
	char *a = malloc(8);
	ft_strcpy(a, "Pad me12");
	print_bytes(a, ft_strlen(a));
	a = des_pad(a, ft_strlen(a));
	print_bytes(a, 19);

	return 1;
}
