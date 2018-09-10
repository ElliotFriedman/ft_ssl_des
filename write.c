#include "openssl.h"
#include "ft_dprintf/includes/ft_printf.h"

int main()
{
	size_t	i;

	i = 0;
	unsigned char chrblock[8];
	/*	
	 *
	 *		For Testing Purposes
	 *
	 */	
	chrblock[0] = 1;
	chrblock[1] = 35;
	chrblock[2] = 69;
	chrblock[3] = 103;
	chrblock[4] = 137;
	chrblock[5] = 171;
	chrblock[6] = 205;
	chrblock[7] = 239;

	int fd = open("test.txt", O_WRONLY);

	ft_dprintf(fd, "%c", chrblock[0]);
	ft_dprintf(fd, "%c", chrblock[1]);
	ft_dprintf(fd, "%c", chrblock[2]);
	ft_dprintf(fd, "%c", chrblock[3]);
	ft_dprintf(fd, "%c", chrblock[4]);
	ft_dprintf(fd, "%c", chrblock[5]);
	ft_dprintf(fd, "%c", chrblock[6]);
	ft_dprintf(fd, "%c", chrblock[7]);

}
