#include <limits.h>
#include "openssl.h"
#include <stdio.h>

/*
unsigned long long	pow2(size_t amt, unsigned long long ret)
{
	//unsigned long long int	ret;

	//ret = 1;
	while (amt--)
		ret <<= 1;
	return (ret);
}
*/

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
//	ft_printf("%064b\n", 108086391056891904);
//	ft_printf("%064b\n", 108086391056891904 >> 56);//& 0x100000000000000ul);
//	ft_printf("%08b\n", (108086391056891904 >> 56) & 1);
//	ft_printf("%064b\n", 1);
//	ft_printf("%08b\n", 127);
//	ft_printf("%08d\n", (127 & pow2(1)) >> 1);

	char a = -1;

	ft_printf("\n\n\n\n\n\n\n%u\n\n\n\n\n\n", UINT_MAX);

	ft_printf("%08b\n", 15);


	ft_printf("%032b\n", 1 << 31);

	ft_printf("strlen: %d\n", ft_strlen("011100101010110111010110110110110011010100011101"));

	ft_printf("strlen: %d\n", ft_strlen("00011011000000101110111111111100011100000111001"));
//	ft_printf("%llu\n%llu\n", pow2(30, 3), pow2(31, 1));
	//ft_printf("%llu\n", pow2(63));
	return 0;
}
