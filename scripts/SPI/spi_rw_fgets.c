#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>


#define ARRAY_SIZE(array) sizeof(array)/sizeof(array[0])


int main(int argc, char **argv) 
{
	int i,fd,x;
	char wr_buf[]={0xff,0x00,0x1f,0x0f};
	char rd_buf[6];
	FILE *fp;

	fd = open(argv[1], O_RDWR);
	
	
	while(1) 
	{
		
	
		if (argc<2) {
			printf("Usage:\n%s [device]\n", argv[0]);
			exit(1);
		}
	   	
	
		if (fd<=0) { 
			printf("%s: Device %s not found\n", argv[0], argv[1]);
			exit(1);
		}
	
		
		 x=fgets(fd, rd_buf, ARRAY_SIZE(rd_buf));
		 if(x>0)
		 {
			printf("%s\n", rd_buf);
		 }
	 	 else
			printf("Error");
			  
		sleep(3);
	}
	
	close(fd);
	return 0;
	
}
