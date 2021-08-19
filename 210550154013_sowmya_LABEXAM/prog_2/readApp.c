#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "Header.h"

int main()
{
	int FileDesc;
	char kbuf[100];
	FileDesc=open("/dev/MyIOCTlDevice",O_RDONLY,0777);
	if(FileDesc < 0)
	{
		printf("Error in opening device.\n");
		return 0;
	}
	
	printf("Reading value from the kernel\n");
	read(FileDesc,kbuf,100);
	printf("closing the driver\n");
	close(FileDesc);
}
	
