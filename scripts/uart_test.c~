#include <stdio.h>

#include <stdlib.h>

#include <fcntl.h>

#include <termios.h>

int fd;

int tty_init (void)
{

	struct termios tio;
	// Open the comms device

//	fd=open("/dev/ttyO0",O_RDWR|O_NOCTTY|O_NONBLOCK); //Open ttyO1 port this will open omap's ttyO1 port
	fd=open("/dev/ttyO0",O_RDWR); //Open ttyO1 port this will open omap's ttyO1 port

	if(fd < 0)
		return 0; //If no file descriptor return 0 error
	else
		printf("File Descriptor: %d\n", fd); //Print value of file descriptor
	 // Set port parameters
	tio.c_cflag = B115200| CS8 | CREAD | CLOCAL; //Set baud, no. of bits,

	tio.c_iflag = IGNPAR | ICRNL; //Ignore parity

	tio.c_oflag = 0;

	tio.c_lflag = ICANON;
	// tio.c_lflag &= ~(ECHO | ICANON);

	tio.c_cc[VMIN] = 2;

	tio.c_cc[VTIME] = 0;

	tcflush(fd, TCIFLUSH);

	tcsetattr(fd,TCSANOW,&tio);
	return 1; //Return to main function with no error

}

void write_tx(char tx)
{
	int ret;
	ret=write(fd,&tx,1);

	if(ret <= 0)
		printf(" no writing takes place:error/n");
	else
		printf(" the written char is %c\n",tx);

}

void read_rx()

{
	char rx;
	int ret;
	int i;
	printf("read func");
	ret=read(fd,&rx,1);
	if(ret < 0)
		perror(" no reading takes place");
	else
		printf("uart read=>%c\n",rx);
}

int main()
{

	int ret;
	ret = tty_init();
	if(ret == 0)
		perror(" cant open the device\n");
	else
		printf("tty successfully initialized\n");

	//while(1)
	//{
		write_tx('c');
		//write_tx('d');
		//write_tx('a');
		//write_tx('c');
		read_rx();
		//sleep(1);
	//}


return 0;
}
