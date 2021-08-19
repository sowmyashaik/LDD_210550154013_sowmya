#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "Header.h"

struct data
{
	int size;
	char buff[];
	int r_w;
};

int main()
{
	int FileDesc;
	int val;
	struct data readdata;
	FileDesc=open("/dev/MyIOCTlDevice",O_RDONLY,0777);
	if(FileDesc < 0)
	{
		printf("Error in opening device.\n");
		return 0;
	}
	
	printf("Writing to driver using ioctl\n");
	ioctl(FileDesc,GETSTATS,&readdata);
	printf("closing the driver\n");
	close(FileDesc);
}
	
