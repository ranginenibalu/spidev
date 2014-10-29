#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include<linux/types.h>
#include<math.h>
#include<string.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

static const char *device = "/dev/spidev3.1";
static uint8_t mode=0;
static uint8_t bits = 8;
static uint32_t speed = 3500000;
static uint16_t delay=30;

char START[5] = "5120";
char len[5];
char payload[15];
static int count = 0;
pthread_t t[10];
int flag[10];
void write_file(char * payload);

struct sensor_info
{
	short int net_id; //2 bytes
	char addr[9]; //8 bytes
	unsigned char sensor_id; //1 byte
	char sensor_val[7]; // 6 bytes
	short int timestamp; //2 bytes
	short int lqi; //2 bytes
};
 


void accept_bytes(char * x)
{
	int i,j=0,n;
	char st[4];
	
	for(i=0;i<4;i++)
	{	st[i] = x[i];
		j++;
	}

	
	if(strcmp(st,START)==0 )
	{
		for(i=0;i<4;i++)
		{
			len[i]=x[j];
			j++;
		}
		n=atoi(len);
		printf("len:%d\n",n);
		for(i=0;i<n;i++,j++)
		{
			payload[i]=x[j];
		}
		
		//for(i=0;i<n;i++)
		//{
			printf("payload is: %s\n",payload);
			write_file(payload);	
		//}
	}
	else
		printf("error\n");
//	return 0;
}

void write_file(char * payload)
{
	int i, j=0;
	sensor_info si;
	char x[2];
	short int n;
	
	//net_id
	char s[2];
	s[0]=payload[j++];
	s[1]=payload[j++];
	n=atoi(s);
	si.net_id=n;
	
	
	//addr
	for(i=0;i<8;i++)
		si.addr[i]=payload[j++];
	si.addr[i]='\0';
	
	//sensor_id
	si.sensor_id=payload[j++];
	
	for(i=0;i<6;i++,j++)
		si.sensor_val[i]=payload[j];
	si.sensor_val[i]='\0';
		
	
	x[0]=payload[j++];
	x[1]=payload[j++];
	si.timestamp=atoi(x);
	
	x[0]=payload[j++];
	x[1]=payload[j++];
	si.lqi=atoi(x);
	
	/*fstream fp;
	fp.open("store1.dat",ios::out|ios::app|ios::binary);
	if(!(fp.write((char *) &si, sizeof(struct sensor_info))))
	{
		printf("error in writing to the file");
	} */
	
	printf("netid:%d\n",si.net_id);
	printf("addr:%s\n",si.addr);
	printf("sensor_id:%d\n",si.sensor_id);
	printf("sensor_val:%s\n",si.sensor_val);
	printf("timestamp:%d\n",si.timestamp);
	printf("lqi:%d\n",si.lqi);
	
}


static void pabort(const char *s)
{
	perror(s);
	abort();
}


static void transfer(int fd)
{
	for(int j=0;j<10;j++)
		flag[j]=0;

	int ret,i;
	uint8_t tx;	
	uint8_t rx;
	
	unsigned long temp;
			
	struct spi_ioc_transfer tr = {
		//.tx_buf = (unsigned long)&tx,
		.rx_buf = (unsigned long)&rx,
		.len = sizeof(tx),
		.delay_usecs = delay,
		.speed_hz = speed,
		.bits_per_word = bits,
		};
		//printf("tx:%ld, rx:%ld", tr.tx_buf, tr.rx_buf);
		
		while(1)
		{
			ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
			if (ret < 1)
				pabort("can't send spi message");
		
			printf("After Receiving. rx:%x\n",rx);
			if(count < 10)
			{
				for(int i=0;i<10;i++)
					if(flag[i] == 0)
					{
						pthread_create( &t[i], NULL, function1, NULL);//create a thread running function1
						flag[i] = 1;
						count++;
						break;
					} 
					
			}
			else
				sleep(1);
			
			for(i=0;i<count;i++)
				if(flag[i] == 2 )
				{	pthread_join( t[i], NULL);
					flag[i] = 0;
					count--;
				}
			
			
			sleep(1);
		}	
}


static void print_usage(const char *prog)
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

static void parse_opts(int argc, char *argv[])
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

int main(int argc, char *argv[])
{
	int ret = 0;
	int fd;
        //mode |= SPI_MSB_FIRST;
	parse_opts(argc, argv);

	fd = open(device, O_RDWR);
	if (fd < 0)
		pabort("can't open device");

	
	ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
	if (ret == -1)
		pabort("can't set spi mode");

	
	/*
	 * bits per word
	 */
	ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (ret == -1)
		pabort("can't set bits per word");


	/*
	 * max speed hz
	 */
	ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret == -1)
		pabort("can't set max speed hz");


	printf("spi mode: %d\n", mode);
	printf("bits per word: %d\n", bits);
	printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000);

	transfer(fd);

	close(fd);

	return ret;
}
