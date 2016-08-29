#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

struct r2k_data {
        unsigned long *addr;
        unsigned long len;
        unsigned long *buff;
};


int main(int argc, char **argv)
{

	int fd;
	int ret;
	unsigned int ioctl_n;
	char *devicename = "/dev/r2";
	struct r2k_data data;
	unsigned long *p;
	int n_words;
	int i;

	n_words = atoi (argv[1]);

	data.buff = malloc (n_words * sizeof (unsigned long));

	fd = open (devicename, O_RDONLY);
	if( fd == -1 ) {
		perror ("error\n");
		return -1;
	}

	data.addr = 0xc1002bd0;
	data.len = sizeof (unsigned long) * n_words;
	printf ("Number of words to take: %d\n", data.len / (sizeof(void *)));
	
	ioctl_n = _IOR ('k', 1, struct r2k_data);
	ret = ioctl (fd, ioctl_n, &data);

	printf ("Got the state: addr: 0x%lx - value: ", data.addr);
	for (i = 0; i < n_words; i++) {
		printf ("0x%08lx ", data.buff[i]);
	}

	printf ("\n");

	close (fd);
	
	return 0;
}
