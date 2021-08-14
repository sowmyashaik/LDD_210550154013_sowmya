#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
	int fd,var_rd1, var_rd2;
	fd = open("/dev/sample_cdev", O_RDONLY,0777);
	if(fd < 0)
	{
		printf("Unable to open the file\n");
		return (-1);
	}
	
	//Fork the process and performing concurrent read on device
	if(fork() == 0)
	{
		read(fd, &var_rd1, sizeof(&var_rd1));
		printf("Reading the first value: %d\n",var_rd1);
		exit(0);
	}
	else
	{
		read(fd, &var_rd2, sizeof(&var_rd2));
		printf("Reading the second value: %d\n",var_rd2);
		wait(NULL);
	}
	close(fd);
	
}
		
