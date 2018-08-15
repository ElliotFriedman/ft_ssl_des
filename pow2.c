#include "ft_printf/includes/ft_printf.h"

//see if we can grab bits like this

unsigned long long	pow2(size_t amt)
{
	unsigned long long	ret;

	ret = 1;
	while (amt--)
		ret *= 2;
	return (ret);
}

int		main()
{
	ft_printf("%064b\n", 108086391056891904 & pow2(56));

	return 0;
}
