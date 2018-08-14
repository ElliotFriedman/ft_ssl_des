#include <limits.h>
#include "openssl.h"
#include <stdio.h>

int main()
{
/*	for (int i = 0; i < 64; i++)
	{
		printf("%d", i % 10);
	}
	printf("\n");
	printf("%llX\n", ULONG_MAX);
	ft_printf("%064b\n", ULLONG_MAX);
*///	ft_printf("%064b\n", /*9223372036854775807*/  0xFFFFFFF00);
	//ft_printf("%064b\n", /*18446744073709551615*/  (0xFFFFFFF000000000ul));

//	ft_printf("%032b %032b\n", (1383827165325090801 >> 32) & 0xFFFFFFFF, 1383827165325090801 & 0xFFFFFFFF);
	//ft_printf("%064b\n", (0x01000000000000000ul << 2));

	//ft_printf("%064b\n", 144115188075855872);
	//ft_printf("%064b\n", 1383827165325090801);
	//0000000110000000000000000000000000000000000000000000000000000000
	ft_printf("%064b\n", 108086391056891904);
	ft_printf("%064b\n", 108086391056891904 >> 56);//& 0x100000000000000ul);
	//
	ft_printf("%08b\n", (108086391056891904 >> 56) & 1);
	ft_printf("%064b\n", 1);
	return 0;
}
