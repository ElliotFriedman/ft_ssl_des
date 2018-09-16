#include "includes/ft_dprintf.h"
#include <fcntl.h>

int main()
{
	size_t	i;

	i = 0;
	unsigned char chrblock[8];
	chrblock[0] = 1;
	chrblock[1] = 35;
	chrblock[2] = 69;
	chrblock[3] = 103;
	chrblock[4] = 137;
	chrblock[5] = 171;
	chrblock[6] = 205;
	chrblock[7] = 239;

	int fd = open("test.txt", O_WRONLY | O_CREAT);

	write(fd, &chrblock[0], 1);
	write(fd, &chrblock[1], 1);
	write(fd, &chrblock[2], 1);
	write(fd, &chrblock[3], 1);
	write(fd, &chrblock[4], 1);
	write(fd, &chrblock[5], 1);
	write(fd, &chrblock[6], 1);
	write(fd, &chrblock[7], 1);

//	ft_dprintf(fd, chrblock[1], 1);
	ft_dprintf(fd, "%c", chrblock[2]);
	ft_dprintf(fd, "%c", chrblock[3]);
	ft_dprintf(fd, "%c", chrblock[4]);
	ft_dprintf(fd, "%c", chrblock[5]);
	ft_dprintf(fd, "%c", chrblock[6]);
	ft_dprintf(fd, "%c", chrblock[7]);
	close(fd);
}
