#include <stdio.h>

#include <stdlib.h>

#include <fcntl.h>
#include <string.h>
#include <termios.h>
int fd;
int tty_init (void)

{

	struct termios tio;
	// Open the comms device

	//fd=open("/srv/tftp/hi.txt",O_RDWR | O_NONBLOCK | O_NOCTTY); //Open ttyS1 port
	fd=open("/dev/ttyO0",O_RDWR); //Open ttyS1 port

	if(fd < 0)
	return 0; //If no file descriptor return 0 error
	else
	printf("File Descriptor: %d\n", fd); //Print value of file descriptor
	 // Set port parameters
	tio.c_cflag = B57600 | CS8 | CREAD | CLOCAL; //Set baud, no. of bits,

	tio.c_iflag = IGNPAR; //Ignore parity

	tio.c_oflag = 0;

	tio.c_lflag = 0;

	tio.c_cc[VMIN] = 20;

	tio.c_cc[VTIME] = 0;

	tcflush(fd, TCIFLUSH);

	tcsetattr(fd,TCSANOW,&tio);
	return 1; //Return to main function with no error

}

void write_tx(int tx)
{
	int ret;
	ret=write(fd,&tx,sizeof(tx));

	if(ret <= 0)
	printf(" no writing takes place/n");
	else
	printf(" the written vale is %x\n",tx);

}

void read_rx()

{
	//char rx[100];
	int rx, ret, i;
	//lseek(fd,0,SEEK_SET);
	//for(i=0;i<10;i++)
	//{
	//memset((void*)rx, 0, 100);
	ret=read(fd,&rx,1);
	//rx[4]='\0';
	if(ret < 0)
	perror("No reading takes place");
	else
	printf("uart read=>%x\n",rx);

	//}
	//printf("total bytes read = %d\n",ret);
}

int main(int argc, char **argv)
{


	//char tx[5];
	int tx;
	printf("Enter value to be sent\n");
	scanf("%x",&tx);
	//char tx[1],rx[1];
	int ret;
	ret = tty_init();
	if(ret == 0)
	perror(" cant open the device\n");
	else
	printf("tty successfully initialized\n");

	//write_tx('c');
	//read_rx();
	//iwrite_tx('d');
	//read_rx();
	//write_tx('a');
	//read_rx();
	//write_tx('c');
	printf("reading...\n");
	//while(1){

	write_tx(tx);
	sleep(1);
	read_rx();

	//sleep(2);

	//}


	return 0;
}
