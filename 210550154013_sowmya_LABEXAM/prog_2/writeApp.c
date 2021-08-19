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
	int val;
	char ubuf[]="This is user buffer";
	FileDesc=open("/dev/MyIOCTlDevice",O_WRONLY,0777);
	if(FileDesc < 0)
	{
		printf("Error in opening device.\n");
		return 0;
	}

	printf("writing data to the buffer\n");
	write(FileDesc,ubuf,sizeof(ubuf));
	printf("closing the driver\n");
	close(FileDesc);
}
	
