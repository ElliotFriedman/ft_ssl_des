/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des-encrypt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 18:20:16 by efriedma          #+#    #+#             */
/*   Updated: 2018/08/03 18:44:55 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"


size_t	c_num(size_t num)
{
	if (num % 8 == 0)
		return (num + 8);
	while (num % 8 != 0)
		num++;
	return (num);
}




char	*des-encrypt(unsigned long long key, char *encrypt, size_t len)
{
	//this is where will store all encrypted bytes
	char	print[c_num(len)];
	size_t	i;

	i = 0;
	//pad bytes so that it is a multple of 8
	//
	//Reverse byte order in 8 byte blocks
	//
	//pass 8 byte blocks into encryption algo until done
	//
	//reverse byte order again
	//
	//output the ciphertext to the area specified

	//Make sure to verify the padded bytes are correct when decrypting
	encrypt = des_pad(encrypt, len);
	rev_8byte(encrypt, len);	
	while (i < len)
	{
		

		i += 8;
	}
}
