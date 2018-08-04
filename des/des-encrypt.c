/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des-encrypt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 18:20:16 by efriedma          #+#    #+#             */
/*   Updated: 2018/08/03 20:27:50 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

# define LROT(x, rotate) (x << rotate) | (x >> (32 - rotate))

int		g_rotate[16];

size_t	c_num(size_t num)
{
	if (num % 8 == 0)
		return (num + 8);
	while (num % 8 != 0)
		num++;
	return (num);
}

void	create_subkey(unsigned long long key, size_t *sub_key)
{
	//32 is the midway point. then the last 8 bytes are empty
	//we don't want to grab empty bites
	sub_key[0] = (size_t)(key >> 40);
	sub_key[1] = (size_t)(key >> 8);
}



char	*encrypted_des(char *data, unsigned long long key, size_t *sub_key)
{
	size_t	i;

	i = 0;

	//do a round of 16, and return the result
	while (i < 16)
	{
		//rotate subkeys each round
		sub_key[0] = LROT(sub_key[0], g_rotate[i]);
		sub_key[1] = LROT(sub_key[1], g_rotate[i]);
		

	}
}

char	*des-encrypt(unsigned long long key, char *encrypt, size_t len)
{
	//this is where will store all encrypted bytes
	char	print[c_num(len) + 1];
	//only 28 bits of this should be utilized
	size_t	two_key[2];
	char	*tmp;
	size_t	i;

	i = 0;
	//null terminate this ish
	print[c_num(len)] = 0;
	
		
	//permute original key from 64 bits to 56 bits
	//least sig byte should be 0
	key = init_subkey(key);
	create_subkey(key, two_key);
	
	//pad bytes so that it is a multple of 8
	encrypt = des_pad(encrypt, len);
	//adjust len to the new padded len
	len = c_num(len);
	//Reverse byte order in 8 byte blocks
	rev_8byte(encrypt, len);	
	//loop to encrypt all bytes, 8 bytes at a time
	while (i < len)
	{
		//encrypted des will return malloc'd 8 chars
		tmp = encrypted_des(&encrypt[i], key, two_key);
		//copy these chars to their proper place in print
		ft_strncpy(&print[i], tmp, 8);
		//zero and delete this malloc'd memory
		ft_memdel((void**)&tmp);
		two_key[0]
		i += 8;
	}
	//reverse byte order again
	rev_8byte(encrypt, len);
	//output the ciphertext to the area specified
	//handle output.
	//write to stdout or file descriptor
	//
	//	If decrypting:
	//		Make sure to verify the padded bytes are correct when decrypting
}
