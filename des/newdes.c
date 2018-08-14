/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newdes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 15:15:35 by efriedma          #+#    #+#             */
/*   Updated: 2018/08/10 15:49:17 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

int			g_permute[64] = {58, 50, 42, 34, 26, 18, 10,
	2, 60, 52, 44, 36, 28, 20,
	12, 4, 62, 54, 46, 38, 30,
	22, 14, 6, 64, 56, 48, 40,
	32, 24, 16, 8, 57, 49, 41,
	33, 25, 17, 9, 1, 59, 51,
	43, 35, 27, 19, 11, 3, 61,
	53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7};



unsigned long long	init_subkey(unsigned long long key)
{
	//This is to extract the 56 bit key from 64 bits
	unsigned long long	ret;
	size_t				i;
	size_t				tmp;

	i = 0;
	ret = 0;
	while (i < 56)
	{
		//shift over x bytes, then grab that byte
		tmp = (key >> g_grab[i]) & 1;
		//while (tmp && tmp / 2)
		//	tmp >> 1;
		//add that byte to ret
		ret |= tmp << g_grab[i];
		//ret <<= 1;
		i++;
	}
	return (ret);
}








unsigned long long		i_p(unsigned long long nbr)
{






}







unsigned long long		ascii2long(char *str)
{
	unsigned long long	tmp;
	size_t				i;

	i = 0;
	tmp = 0;
	while (i < 8)
	{
		tmp += str[i];
		if (i + 1 != 8)
			tmp <<= 8;
		i++;
	}
	return (tmp);
}



void					main(unsigned long long int argc)//, char **argv)
{
	//pad text block
	//
	//

}
