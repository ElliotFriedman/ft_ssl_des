#include <limits.h>
#include "openssl.h"
#include <stdio.h>

int main()
{
	printf("append: %d\n",  O_APPEND);
	printf("create: %d\n",  O_CREAT);
	printf("write: %d\n",   O_WRONLY );
	int fd = open("helloworld.c", O_WRONLY | O_CREAT);
	write(fd, "Hello", 5);
	return 0;
}
