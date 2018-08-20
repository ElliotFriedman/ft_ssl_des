/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des-encrypt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 18:20:16 by efriedma          #+#    #+#             */
/*   Updated: 2018/08/19 23:25:26 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

# define LROT(x, rotate) (x << rotate) | (x >> (32 - rotate))

//Debug protocol

//Recheck all globals for errors when algorithm breaks
//Then check that least significant byte(s) are empty
//Then check endianness
//Then check logic errors
//Then check memory issues

//final permutation
int		g_fpermutation[] = {40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41, 9, 49, 17, 57, 25};

//sboxes
int		g_sbox[32][16] = {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
	{0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
	{4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
	{15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
	{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
	{3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
	{0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
	{13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
	{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
	{13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
	{13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
	{1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
	{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
	{13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
	{10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
	{3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
	{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
	{14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
	{4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
	{11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
	{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
	{10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
	{9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
	{4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
	{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
	{13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
	{1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
	{6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
	{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
	{1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
	{7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
	{2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}};

int         g_permute[64];

//compression permutation
int		g_cpermutation[48] = {14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10,
	23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2,
	41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};

//expansion permutation
int		g_expandpermutation[48] = {32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9,
	8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};


int		g_rotate[16] = {1, 1, 2, 2,
	2, 2, 2, 2,
	1, 2, 2, 2,
	2, 2, 2, 1};

unsigned int	g_rsubkey[17];

unsigned int	g_lsubkey[17];

unsigned long long lmax = 0xFFFFFFFFFFFFFFFF;

size_t	c_num(size_t num)
{
	if (num % 8 == 0)
		return (num + 8);
	while (num % 8 != 0)
		num++;
	return (num);
}

//subkey[0] will be the most significant bytes
//subkey[1] will be the least significant bytes

//this function takes 32 bits from bside and turns it 48 bits
unsigned long long	expansion_permutation(unsigned long long bside)
{
	size_t				i;
	unsigned long long	ret;

	i = 0;
	ret = 0;
	while (i < 48)
	{
		//make sure shift evaluates first. 
		//Unsure of bitwise operator precedence
		ret |= (bside >> g_expandpermutation[i]) & 1;
		ret <<= 1;
		i++;
	}
	//leave last 2 bytes empty
	return (ret << 16);
}

unsigned long long	concat_subkeys(size_t *subkeys)
{
	unsigned long long	ret;

	ret = subkeys[1];
	//only first 28 bits of subkeys are used 
	ret <<= 28;
	ret += subkeys[0];
	//least significant byte should be empty
	//ret <<= 8;
	return (ret << 8);
}

//compression permutation
unsigned long long	comp_perm(unsigned long long i56bit)
{
	unsigned long long	i48bit;
	size_t				i;

	i = 0;
	i48bit = 0;
	//get bits in the proper order to be used.
	//usually least sig byte is empty
	//we will change that by shifting
	i56bit >>= 8;
	while (i < 8)
	{
		//grab only the last bit
		i48bit |= (g_cpermutation[i] >> i56bit) & 1;
		i++;
	}
	return (i48bit);
}

//2 blocks that are 2 bits each
char	*l_bytes(unsigned long long aside, unsigned long long bside)
{
	char	*ret;
	char	*cpy;

	cpy = 0;
	ret = ft_memalloc(8);
	cpy = (char *)&aside;
	ret[0] = cpy[0];
	ret[1] = cpy[1];
	ret[2] = cpy[2];
	ret[3] = cpy[3];
	cpy = (char *)&bside;
	ret[4] = cpy[1];
	ret[5] = cpy[1];
	ret[6] = cpy[1];
	ret[7] = cpy[1];
	return (ret);
}

//initial permutation on the 64 bit block of plaintext
unsigned long long	initialperm(unsigned long long txt)
{
	size_t	i;
	unsigned long long	ret;

	i = 0;
	ret = 0;
	while (i < 64)
	{
		ret += ((txt >> (g_permute[i] - 1)) & 1) << i;
		i++;
	}
	return (ret);
}
/*
size_t	rotatex(size_t i)
{
	g_rsubkey[i] = (g_rsubkey[i] << g_rotate[i]) | (28 - g_rotate[i] >> g_rsubkey[i]);
	g_lsubkey[i] = g_rotate[i];
}
*/

void	create_subkeys(unsigned long long key)
{
	size_t	i;
	size_t	ltmp;
	size_t	rtmp;

	i = 0;
	g_rsubkey[0] = (size_t)((key & 0xFFFFFFF000000000ul) >> 32);
	g_lsubkey[0] = (size_t)(key & 0xFFFFFFF00) >> 4;

	ft_printf("rsubkey:	%032b\n", g_rsubkey[0]);
	ft_printf("lsubkey:	%032b\n", g_lsubkey[0]);
	while (i < 16)
	{
		if (i)
		{
			g_lsubkey[i] = g_lsubkey[i - 1];
			g_rsubkey[i] = g_rsubkey[i - 1];
		}
		ltmp = (g_rotate[i] == 1 ? 1 << 31: 3 << 30) & g_lsubkey[i];
		rtmp = (g_rotate[i] == 1 ? 1 << 31: 3 << 30) & g_rsubkey[i];
		g_lsubkey[i] <<= g_rotate[i];
		g_rsubkey[i] <<= g_rotate[i];
		g_lsubkey[i] += ltmp >> (g_rotate[i] == 1 ? 27 : 26);
		g_rsubkey[i] += rtmp >> (g_rotate[i] == 1 ? 27 : 26);
		ft_printf("\nrsubkey:         %032b\n", (size_t)g_rsubkey[i]);
	   	ft_printf("lsubkey:         %032b\n", (size_t)g_lsubkey[i]);
		i++;
	}
}

char	*encrypted_des(char *data, unsigned long long key, size_t *sub_key)
{
	size_t				i;
	unsigned long long	aside;
	unsigned long long	bside;
	//this will store the next L(i) value
	unsigned long long	aside_next;

	i = 0;
	aside = 0;
	bside = 0;
	//do the initial permutation on the 64 block of text
	key = initialperm(key);
//	 ft_printf("Before memcpy iteration \n");
	//break data into 2 4 byte blocks
	//ft_strncpy((char*)&g_rsubkey, data, 4);
	//ft_strncpy((char*)&g_lsubkey, data, 4);


	//debug ciphertext
	//	ft_printf("%032b %032b\n", aside, bside);
	
	//shift b right 32 times so that bytes are in order to be manipulated in exp_permute
	bside >>= 32;
	//do a round of 16, and return the result
	while (i < 16)
	{
		 //ft_printf("In while loop iteration %d\n", i);
		//grab current bside value as it will change in this loop
		aside_next = bside;
		//run expansion permutation on bside
		//
		//									then compress	(concatenate subkeys)
		bside = expansion_permutation(bside);

		//precompute subkeys

		//rotate subkeys each round
		//This is wrong needs to be Compressed,
		
		key = concat_subkeys(sub_key);
		expansion_permutation(concat_subkeys(sub_key));


		//after you have done all logic in iteration x, reassign aside to bside b4 modification
		bside = aside ^ bside;
		aside = aside_next;
		i++;	
	}
	//merge aside and bside
	//l_bytes(aside, bside);
	//perform final permutation on aside and bside merged
	//final_permutate();
	//return (final_permutate(l_bytes(aside, bside)));
	return (l_bytes(aside, bside));
}
void	debug_num(void)
{
	size_t	i = -1;

	ft_putstr("0123");
	while (++i < 64)
		ft_putnbr(i % 10);
	ft_putstr("\n");
}

char	*des_encrypt(unsigned long long key, char *encrypt, size_t len)
{
	//this is where will store all encrypted bytes
	char	*print;
	//only 28 bits of this should be utilized
	size_t	two_key[2];
	char	*tmp;
	size_t	i;

	i = 0;
	print = ft_memalloc(len + 1);
	//null terminate this ish
	print[c_num(len)] = 0;

	//permute original key from 64 bits to 56 bits
	//least sig byte should be 0
	//rev_8byte((char*)&key, 8);
//	ft_printf("key in dencr: %064b\n", key);
	
	key = init_subkey(key);
	ft_putstr("\n\npermuted key: ");
	debug_num();
	ft_printf("permuted key: %064b\n\n\n", key);
	//create_subkey(key, two_key);

	//pad bytes so that it is a multple of 8
	encrypt = des_pad(encrypt, len);
	//adjust len to the new padded len
	len = c_num(len);
	//Reverse byte order in 8 byte blocks. little->big endian
	rev_8byte(encrypt, len);	
	//loop to encrypt all bytes, 8 bytes at a time
	while (i < len)
	{
		//ft_printf("In while loop iteration %d\n", i);
		//encrypted des will return malloc'd 8 chars
		tmp = encrypted_des(&encrypt[i], key, two_key);
		//ft_putstr(tmp);
		//copy these chars to their proper place in print
		ft_strncpy(&print[i], tmp, 8);
		//zero and delete this malloc'd memory
		ft_memdel((void**)&tmp);
		
		// 	?????
		//two_key[0];
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
	create_subkeys(key);
	return (print);
}
