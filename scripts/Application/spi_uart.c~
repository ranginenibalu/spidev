#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <linux/types.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <termios.h>
#include<string.h>
#include "complete_app1.c"
#include "server_file.c"

#define MAX 42

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))



//void convert( (void *) struct data obj);

static void pabort(const char *s)
{
	perror(s);
	abort();
}

static const char *device = "/dev/spidev3.1";
static uint8_t mode=0;
static uint8_t bits = 8;
static uint32_t speed = 2000000;
static uint16_t delay=30;
static int fd1, fd2;

static void  spi();
void  uart();


int tty_init (void) // Function to initialize UART
{
	struct termios tio;
	// Open the comms device

	//fd=open("/srv/tftp/hi.txt",O_RDWR | O_NONBLOCK | O_NOCTTY); //Open ttyS1 port
	fd2=open("/dev/ttyO0",O_RDWR); //Open ttyS1 port

	if(fd2 < 0)
	return 0; //If no file descriptor return 0 error
	else
	printf("File Descriptor: %d\n", fd2); //Print value of file descriptor
	 // Set port parameters
	tio.c_cflag = B57600 | CS8 | CREAD | CLOCAL; //Set baud, no. of bits,

	tio.c_iflag = IGNPAR; //Ignore parity

	tio.c_oflag = 0;

	tio.c_lflag = 0;

	tio.c_cc[VMIN] = MAX;

	tio.c_cc[VTIME] = 0;

	tcflush(fd2, TCIFLUSH);

	tcsetattr(fd2,TCSANOW,&tio);
	return 1; //Return to main function with no error

}


static void spi() // Function to transfer via SPI
{
	int ret,i,k;
	char *tx="aaaaA", str;	
	char rx[MAX], rx1[20],ch;
	
   	
	//unsigned long tx;
	//unsigned long rx=0;
	unsigned long temp;
	//__u64 rx;
 	//	__u64 tx;	
	
	//printf("\nEnter a value");
	//scanf("%c",&tx);
	//tx -=48;
	//temp = (unsigned long)tx;
	//printf("\n\n test. long:%ld , char:%c\n\n\n", temp, tx);
	//tx = i;
	
	
			
	struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)tx,
		.rx_buf = (unsigned long)rx,
		.len = MAX,
		.delay_usecs = delay,
		.speed_hz = speed,
		.bits_per_word = bits,
		//.cs_change = 1,
		};
		//printf("tx:%ld, rx:%ld", tr.tx_buf, tr.rx_buf);
		
		/*while(1)
		{

			memset((void*)tr.rx_buf, 0, 100);
			ret = ioctl(fd1, SPI_IOC_MESSAGE(1), &tr);
			if (ret < 1)
				pabort("can't send spi message");
			//rx[5] = '\0';
			//
			if(rx)
			{
				printf("After Receiving. rx:%s\n",rx);
				accept_bytes(rx, "log_spi.dat");
				//printf("rx:%ld", tr.rx_buf);
			}
			sleep(3);
		}*/
		
		while(1)
		{
			memset((char *)rx, 0, MAX);
			//digitalWrite(tr.cs_change, 0);
			ret = ioctl(fd1, SPI_IOC_MESSAGE(1), &tr);
			if (ret < 1)
				pabort("can't send spi message");
			//rx[5] = '\0';
			//for(i=1;i<20;i++)
			printf("\nSPI=>After Receiving. %s",rx);
			printf("\n");
			k = 0;
			
			//str=fgets(str, 20, fd1);
			
			/*while (k <16)
				{	
					sprintf (rx1[k], "%x", rx[k]);
					k++;
				}
				printf("\n");*/
			
			/*sscanf(rx, "%s%s%s", rx1);*/
			//for(k=0;k<20;k++)
			//printf("After Receiving. %x\n",rx1[k]);
			
						
		
			convert(rx, "log_spi.dat");
			//accept_bytes(rx, "abc");
			//printf("rx:%ld", tr.rx_buf);
			sleep(4);
		}
		
		
}


static void print_usage(const char *prog) // Not Important
{
	printf("Usage: %s [-DsbdlHOLC3]\n", prog);
	puts("  -D --device   device to use (default /dev/spidev1.1)\n"
	     "  -s --speed    max speed (Hz)\n"
	     "  -d --delay    delay (usec)\n"
	     "  -b --bpw      bits per word \n"
	     "  -l --loop     loopback\n"
	     "  -H --cpha     clock phase\n"
	     "  -O --cpol     clock polarity\n"
	     "  -L --lsb      least significant bit first\n"
	     "  -C --cs-high  chip select active high\n"
	     "  -3 --3wire    SI/SO signals shared\n");
	exit(1);
}

static void parse_opts(int argc, char *argv[]) // Argument Parser for SPI
{
	while (1) {
		static const struct option lopts[] = {
			{ "device",  1, 0, 'D' },
			{ "speed",   1, 0, 's' },
			{ "delay",   1, 0, 'd' },
			{ "bpw",     1, 0, 'b' },
			{ "loop",    0, 0, 'l' },
			{ "cpha",    0, 0, 'H' },
			{ "cpol",    0, 0, 'O' },
			{ "lsb",     0, 0, 'L' },
			{ "cs-high", 0, 0, 'C' },
			{ "3wire",   0, 0, '3' },
			{ "no-cs",   0, 0, 'N' },
			{ "ready",   0, 0, 'R' },
			{ NULL, 0, 0, 0 },
		};
		int c;

		c = getopt_long(argc, argv, "D:s:d:b:HOLC3NR", lopts, NULL);

		if (c == -1)
			break;

		switch (c) {
		case 'D':
			device = optarg;
			break;
		case 's':
			speed = atoi(optarg);
			break;
		case 'd':
			delay = atoi(optarg);
			break;
		case 'b':
			bits = atoi(optarg);
			break;
		case 'l':
			mode |= SPI_LOOP;
			break;
		case 'H':
			mode |= SPI_CPHA;
			break;
		case 'O':
			mode |= SPI_CPOL;
			break;
		case 'L':
			mode |= SPI_LSB_FIRST;
			break;
		case 'C':
			mode |= SPI_CS_HIGH;
			break;
		case '3':
			mode |= SPI_3WIRE;
			break;
		case 'N':
			mode |= SPI_NO_CS;
			break;
		case 'R':
			mode |= SPI_READY;
			break;
		default:
			print_usage(argv[0]);
			break;
		}
	}
}


void uart()

{
	char rx[MAX];
	int ret, i;
	
	//lseek(fd,0,SEEK_SET);
	//for(i=0;i<10;i++)
	//{
	while(1) 
	{
		memset((char *)rx, 0, MAX);
		ret=read(fd2,rx,MAX);
		if(ret < 0)
		perror("No reading takes place");
	
		else
		{
			printf("\nuart read=>");
			for(i=0;i<MAX;i++)
				printf("%x ",rx[i]);
			sleep(1);
			
			convert(rx, "log_uart.dat");
		}
		
		sleep(1);
	}
}



int main(int argc, char *argv[])
{
	int ret = 0;
	int retu;
	pthread_t t1, t2 ; // declare 2 threads.
	
	parse_opts(argc, argv);

			
	
//SPI 
	fd1 = open(device, O_RDWR);
	if (fd1 < 0)
		pabort("can't open spi device file");

	ret = ioctl(fd1, SPI_IOC_WR_MODE, &mode);
	if (ret == -1)
		pabort("can't set spi mode");

	/*
	 * bits per word
	 */
	ret = ioctl(fd1, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (ret == -1)
		pabort("can't set bits per word");

	/*
	 * max speed hz
	 */
	ret = ioctl(fd1, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret == -1)
		pabort("can't set max speed hz");



//UART
	
	retu = tty_init();
	if(retu == 0)
		perror(" cant open the uart device file\n");
	else
		printf("uart: tty successfully initialized\n");
		
	
	//printf("spi mode: %d\n", mode);
	//printf("bits per word: %d\n", bits);
	//printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000);

		
   	pthread_create( &t1, NULL, spi, NULL); // create a thread running function1
    	
    	pthread_create( &t2, NULL, uart , NULL); // create a thread running function2

	pthread_join(t1,NULL) ;
 	pthread_join(t2,NULL) ;
	
	close(fd1);
	close(fd2);

	return ret;
}
