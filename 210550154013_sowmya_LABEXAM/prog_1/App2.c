#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>


int main()
{
	int fd;
	char write_buf2[] = "Hello kernel .. This is dev2";
	char read_buf2[100] = "\0";
	fd = open("/dev/mycdev2",O_RDWR,0777);
	if(fd < 0)
	{
		printf("Unable to open the file\n");
		return (-1);
	}
        write(fd,write_buf2, sizeof(write_buf2));
        read(fd, read_buf2, sizeof(read_buf2));
	close(fd);
	return 0;
	
}
