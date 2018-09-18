#include "openssl.h"
#include <string.h>

void	changeval(char *str)
{	
	size_t	i;

	i = 0;
	printf("%p\n", &str);
	while (str[i])
	{
		str[i] += 1;
		i++;
	}
}

int main()
{
	char *str = malloc(6);
	strcpy(str, "hello");
	char	*test;
	printf("main %p\n", &test);

	 test = str;
	printf("main %p\n", &str);
	printf("main %p\n", &test);
	changeval(test);
	ft_putstr(str);
}

