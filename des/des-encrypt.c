/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des-encrypt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 18:20:16 by efriedma          #+#    #+#             */
/*   Updated: 2018/09/08 00:49:40 by efriedma         ###   ########.fr       */
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
int					g_fperm[64] = {40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41, 9, 49, 17, 57, 25};

//sboxes
int					g_sbox[32][16] = {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
	{0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
	{4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},	//i must be 0-3 to finish this
	{15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},

	{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
	{3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
	{0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15}, //i must be 4-7
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

//32 rows, 16 values per row

int     		    g_permute[64];

//compression permutation
/*int					g_cpermutation[48] = {14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10,
  23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2,
  41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
  44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};
  */
int					g_cpermutation[48] = {14,    17,   11,    24,     1,    5,
	3,     28,   15,     6,    21,   10,
	23,    19,   12,     4,    26,    8,
	16,     7,   27,    20,    13,    2,
	41,    52,   31,    37,    47,   55,
	30,    40,   51,    45,    33,   48,
	44,    49,   39,    56,    34,   53,
	46,    42,   50,    36,    29,   32};

//expansion permutation
int					g_expandpermutation[48] = {32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9,
	8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};


int					g_rotate[16] = {1, 1, 2, 2,
	2, 2, 2, 2,
	1, 2, 2, 2,
	2, 2, 2, 1};

//not sure where we use this
unsigned long long	g_arr[16];

unsigned int		g_rsubkey[16];

unsigned int		g_lsubkey[16];

unsigned long long	g_concatsubkeys[16];

//store 48 bit subkey
//This will get XOR'ed with the 48 bit right
//block that goes through an expansion permutation
unsigned long long	g_k[16];

unsigned long long	lmax = 0xFFFFFFFFFFFFFFFF;

size_t				c_num(size_t num)
{
	if (num % 8 == 0)
		return (num + 8);
	while (num % 8 != 0)
		num++;
	return (num);
}

unsigned long long	permuterightside(unsigned long long rside)
{
	unsigned long long	ret;
	size_t				i;
	unsigned long long	tmp;

	i = 0;
	ret = 0;
	ft_printf("rightside: %064b\n", rside);
	while (i < 48)
	{
		tmp = (pow2(g_expandpermutation[i] - 1) & rside);
//			ft_printf("bit we grabbed:	  %064b\n",tmp);
		if (((g_expandpermutation[i] + 1) > (int)i) && (g_expandpermutation[i] != (int)i))
			tmp <<= (g_expandpermutation[i] - i - 1);
		else if (g_expandpermutation[i] != (int)i)
			tmp >>= i - (g_expandpermutation[i] - 1);
		else if (g_expandpermutation[i] == (int)i)
			tmp >>= 1;
		ret += (tmp);
		i++;
	}
		ft_printf("\n48 bit right side expansion:		= %064b\n", ret);
	return (ret);
}

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

//hard cased for 5 & 30, could be wrong, will check later if need be
unsigned long long	permute_concatsubkeys(size_t x)
{
	unsigned long long	ret;
	size_t				i;
	unsigned long long	tmp;

	i = 0;
	ret = 0;
	//	ft_printf("\n56 bit shuffled	= %064b\n", g_arr[x]);
	while (i < 48)
	{
		tmp = (pow2(g_cpermutation[i] - 1) & g_arr[x]);
		if (((g_cpermutation[i] + 1) > (int)i) && (g_cpermutation[i] != (int)i))
			tmp <<= (g_cpermutation[i] - i - 1);
		else if (g_cpermutation[i] != (int)i)
			tmp >>= i - (g_cpermutation[i] - 1);
		else if (g_cpermutation[i] == (int)i)
			tmp >>= 1;
		ret += (tmp);
		i++;
	}
		ft_printf("\n48 bit subkey from permuted subkey		= %064b\n", ret);
	return (ret);
}

void				concat_subkeys(void)
{
	size_t				i;
	//unsigned long long	arr[16];

	i = 0;
	while (i < 16)
	{
		g_arr[i] = g_rsubkey[i];
//				ft_printf("subkey:		%064b\n", g_arr[i]);
		g_arr[i] <<= 28;
//				ft_printf("subkey:		%064b\n", g_arr[i]);
		g_arr[i] += (g_lsubkey[i]);
//				ft_printf("subkey:		%064b\n", g_arr[i]);
		g_arr[i] <<= 4;
//				ft_printf("subkey	%d:	%064b\n\n\n", i, g_arr[i]);
		i++;
	}
	i = 0;
	while (i < 16)
	{
		g_k[i] = permute_concatsubkeys(i);
		ft_printf("g_k:						%064b\n", g_k[i]);
		i++;
	}
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

//This function works
void	create_subkeys(unsigned long long key)
{
	size_t	i;
	size_t	ltmp;
	size_t	rtmp;

	i = 0;
	g_rsubkey[0] = (size_t)((key & 0xFFFFFFF000000000ul) >> 32);
	g_lsubkey[0] = (size_t)(key & 0xFFFFFFF00) >> 4;

	//	ft_printf("rsubkey:	%032b\n", g_rsubkey[0]);
	//	ft_printf("lsubkey:	%032b\n", g_lsubkey[0]);
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
//				ft_printf("\nrsubkey:         %032b\n", (size_t)g_rsubkey[i]);
//			   	ft_printf("lsubkey:         %032b\n", (size_t)g_lsubkey[i]);
		i++;
	}
	concat_subkeys();
}

void	init_txtblock(unsigned long long *block, unsigned char *chrblock)
{
	size_t	i;

	i = 0;
	*block = 0;
	
/*	
 *
 *		For Testing Purposes
 *
 */	chrblock[0] = 1;
	chrblock[1] = 35;
	chrblock[2] = 69;
	chrblock[3] = 103;
	chrblock[4] = 137;
	chrblock[5] = 171;
	chrblock[6] = 205;
	chrblock[7] = 239;

//	ft_printf("txt block:   %08b", chrblock[0]);
//	ft_printf("%08b", chrblock[1]);
//	ft_printf("%08b", chrblock[2]);
//	ft_printf("%08b", chrblock[3]);
//	ft_printf("%08b", chrblock[4]);
//	ft_printf("%08b", chrblock[5]);
//	ft_printf("%08b", chrblock[6]);
//	ft_printf("%08b\n", chrblock[7]);

//		ft_printf("Looking at textblock");
	while (i < 8)
	{
		*block += chrblock[i];
		if (i + 1 != 8)
			*block <<= 8;
//		ft_printf("\nprint as we go:	%064b\n", *block);
		i++;
	}
//	ft_printf("txt block:	%064b\n", *block);
	//run initial permutation on textblock
	*block = initial_perm(*block);
}

unsigned long long	sboxes(unsigned long long expandrside)
{
	unsigned long long	ret;
	size_t				i;
	size_t				tmp;

	i = 0;
	tmp = 0;
	ret = 0;
	while (i < 32)
	{
//		ft_printf("expandrside:	%064b\n", expandrside);
		tmp = (expandrside & 0xFC00000000000000ul) >> 58;
		
	//	ft_printf("%06b	%06b %06b\n", tmp, i + ((tmp & 1) | ((tmp & 32) >> 4)), (tmp & 60) >> 1);
		
//				ft_printf("row: %02d, index: %02d\n", i + (((tmp & 1) | ((tmp & 32) >> 4)) & 3), (tmp & 30) >> 1);// + (((tmp & 1) | ((tmp & 32) >> 4)) & 3));
		
		ret += g_sbox[i + (((tmp & 1) | ((tmp & 32) >> 4)) & 3)] [(tmp & 30) >> 1];
		
		if (i + 4 != 32)
			ret <<= 4;
		expandrside <<= 6;
		i += 4;
	}
	ret <<= 32;
	ft_printf("sbox output: %064b\n", ret);
	return (ret);
}

unsigned long long	final_permutate(unsigned long long rside)//, unsigned long long lside)
{
	unsigned long long	ret;
	size_t				i;
	unsigned long long	tmp;

	i = 0;
	ret = 0;
	ft_printf("rightside: %064b\n", rside);
	while (i < 64)
	{
		tmp = (pow2(g_fperm[i] - 1) & rside);
//			ft_printf("bit we grabbed:	  %064b\n",tmp);
		if (((g_fperm[i] + 1) > (int)i) && (g_fperm[i] != (int)i))
			tmp <<= (g_fperm[i] - i - 1);
		else if (g_fperm[i] != (int)i)
			tmp >>= i - (g_fperm[i] - 1);
		else if (g_fperm[i] == (int)i)
			tmp >>= 1;
		ret += (tmp);
		i++;
	}
	ft_printf("\nfinal permutation:		= %064b\n", ret);
	return (ret);
}

//unsigned long long	l_bytes(unsigned long long rside, unsigned long long lside)
//{
//	return (rside | (lside >> 32));
//}
char	*l_bytes(unsigned long long aside)
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
	ret[4] = cpy[4];
	ret[5] = cpy[5];
	ret[6] = cpy[6];
	ret[7] = cpy[7];
	return (ret);
}

char	*encrypted_des(char *data, unsigned long long key)
{
	size_t				i;
	unsigned long long	lside;
	unsigned long long	rside;
	unsigned long long	aside_next;
	unsigned long long	textblock;

	i = 0;
	//initialize txtblock
	init_txtblock(&textblock, (unsigned char*)data);
	
	//break data into 2 4 byte blocks
	lside = textblock >> 32;
	lside <<= 32;
	rside = (0xFFFFFFFF & textblock) << 32;
	//rside <<= 32;
	ft_printf("rside:	%064b\n", rside);

	//do the initial permutation on the key
	key = initialperm(key);
	ft_printf("lside:	%064b\n", lside);
	ft_printf("rside:	%064b\n", rside);
	while (i < 16)
	{
		//save right side value before you permute and shift it
		aside_next = rside;
		//permute right side
		rside = permuterightside(rside);
	//	ft_printf("g_k[%d] ^ rside: %064b\n", i, g_k[i] ^ rside);
		//sbox
		rside = sboxes(rside ^ g_k[i]);
		//pbox permutation
		rside = pperm(rside);
		//after you have done all logic in iteration x, reassign aside to bside b4 modification
		rside = lside ^ rside;
		//left side equals previous right side
		ft_printf("Rside after manipulation: %064b\n", rside);
		lside = aside_next;
		i++;
	}
	//perform final permutation on lside and rside merged
	//merge right and then left, due to final key arrangement process
	ft_printf("right block: %064b\nleft block: %064b\n", rside, lside);
	return (l_bytes(final_permutate(rside | (lside >> 32))));
	//return (l_bytes(lside, rside));
}

unsigned long long	swaplong_endian(unsigned long long num)
{
	unsigned long long	b[8];

	b[0] = (num & 0xff) << 56;
	b[1] = (num & 0xff00) << 40;
	b[2] = (num & 0xff0000) << 24;
	b[3] = (num & 0xff000000) << 8;

    b[4] = (num & 0xff00000000) >> 8;
    b[5] = (num & 0xff0000000000) >> 24;
	b[6] = (num & 0xff000000000000) >> 40;
	b[7] = (num & 0xff00000000000000) >> 56;
	return (b[0] | b[1] | b[2] | b[3] | b[4] | b[5] | b[6] | b[7]);
}

void			swap_long_endian(unsigned long long *encrypt, size_t bytes)
{
	size_t			i;

	i = 0;
	while (i < (bytes / 8))
	{
		ft_printf("before endian swap: %016X\n", encrypt[i]);
		encrypt[i] = swaplong_endian(encrypt[i]);
		ft_printf("after endian swap: %016X\n", encrypt[i]);
		i++;
	}
}

char	*des_encrypt(unsigned long long key, char *encrypt, size_t len)
{
	//this is where will store all encrypted bytes
	char	*print;
	//only 28 bits of this should be utilized
	//	size_t	two_key[2];
	char	*tmp;
	size_t	i;

	i = 0;
	print = ft_memalloc(len);

	
	//uncomment this when we are ready to try the algorithm
	//rev_8byte((char*)&key, 8);
	
	key = init_subkey(key);

	//ft_putstr("\n\npermuted key: ");
	ft_printf("permuted key: %064b\n\n\n", key);
	
	//pad bytes so that it is a multple of 8
	encrypt = des_pad(encrypt, len);
	//adjust len to the new padded len
	len = c_num(len);
	//swap_long_endian((unsigned long long *)encrypt, len);
	//Reverse byte order in 8 byte blocks. little->big endian
	//rev_8byte(encrypt, len);
	//loop to encrypt all bytes, 8 bytes at a time
	create_subkeys(key);
	while (i < len)
	{
		//ft_printf("In while loop iteration %d\n", i);
		//encrypted des will return malloc'd 8 chars
		tmp = encrypted_des(&encrypt[i], key);
		//ft_putstr(tmp);
		//copy these chars to their proper place in print
		ft_strncpy(&print[i], tmp, 8);
		//zero and delete this malloc'd memory
		//ft_printf("Output:
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
	return (print);
}
