#include <limits.h>
#include "openssl.h"
#include <stdio.h>

int main()
{

	ft_printf("%08b\n", 15);

	ft_printf("%032b\n", 30);

	ft_printf("%064b\n", 0xFC00000000000000ul >> 58);
	//ft_printf("strlen: %d\n", ft_strlen("11101000001010101101111001101011"));

	return 0;
}
