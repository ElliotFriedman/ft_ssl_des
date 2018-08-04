#include <limits.h>
#include "openssl.h"
#include <stdio.h>

int main()
{
	for (int i = 0; i < 64; i++)
	{
		printf("%d", i % 10);
	}
	printf("\n");
	printf("%llX\n", ULONG_MAX);
	ft_printf("%064b\n", ULLONG_MAX);
	ft_printf("%064b\n", 9223372036854775807 & 0xFFFFFFF00);
	ft_printf("%064b\n", 9223372036854775807 & -(0xFFFFFFF000000000ul));

	return 0;
}
