#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <delay.h>

#define delay 2000

int main()
{
	int fd;
	char write_buf1[] = "Hello kernel .. This is user buffer of dev1";
	char read_buf1[100] = "\0";
	fd = open("/dev/mycdev1",O_RDWR,0777);
	if(fd < 0)
	{
		printf("Unable to open the file\n");
		return (-1);
	}
       msleep(delay);
       write(fd,write_buf1, sizeof(write_buf1));
       read(fd, read_buf1, sizeof(read_buf1));
	close(fd);
	return 0;
	
}
