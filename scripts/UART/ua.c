#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>

#define DEVICE "/dev/ttyUSB0"
#define SPEED B38400 

int main()
{
struct termios tio; //to hold serial port settings
struct termios stdio; //so we can accept user input
    struct termios old_stdio; //save the current port settings
    int tty_fd; //file descriptor for serial port
    int retval, res, n, res2, read1, wri;
    char buf[255];
    char buf2[255]; 


    tty_fd = open(DEVICE, O_RDWR | O_NDELAY);
    if(tty_fd < 0)
    {
        perror(DEVICE);
        exit(-1);
    }
    printf("Init 1 complete.\n");

    tcflush(tty_fd, TCIOFLUSH);

    int f = fcntl(tty_fd, F_GETFL, 0);
    fcntl(tty_fd, F_SETFL, f & ~O_NDELAY);

    retval = tcgetattr(tty_fd, &old_stdio);
    if(retval != 0)
    {
        perror(DEVICE);
        exit(-1);
    }
    printf("Init 2 complete.\n");

    struct termios newtio;
    retval = tcgetattr(tty_fd, &newtio);
    if(retval != 0)
    {
        perror(DEVICE);
        exit(-1);
    }
    printf("Init 3 complete.\n");

    cfsetospeed(&newtio, SPEED);
    cfsetispeed(&newtio, SPEED);

    newtio.c_cflag = (newtio.c_cflag & ~CSIZE) | CS8;
    newtio.c_cflag |= CLOCAL | CREAD;
    newtio.c_cflag &= ~(PARENB | PARODD);
    newtio.c_cflag &= ~CRTSCTS;
    newtio.c_cflag &= ~CSTOPB;

    newtio.c_iflag = IGNBRK;
    newtio.c_iflag &= ~(IXON | IXOFF | IXANY);

    newtio.c_lflag = 0;

    newtio.c_oflag = 0;

    newtio.c_cc[VTIME] = 1;
    newtio.c_cc[VMIN] = 60;
    newtio.c_cc[VINTR] = 127; 
    newtio.c_cc[VQUIT] = 28;
    newtio.c_cc[VERASE] = 8;
    newtio.c_cc[VKILL] =  21;
    newtio.c_cc[VEOF] = 4;
    newtio.c_cc[VSTOP] = 19;
    newtio.c_cc[VSTART] = 17;
    newtio.c_cc[VSUSP] = 26;
    newtio.c_cc[VREPRINT] = 18;
    newtio.c_cc[VFLSH] = 15;
    newtio.c_cc[VWERASE] = 23;
    newtio.c_cc[VLNEXT] = 22;


    retval = tcsetattr(tty_fd, TCSANOW, &newtio);
    if(retval != 0)
    {
        perror(DEVICE);
        exit(-1);
    }
    printf("Init 4 complete.\n");

    int mcs = 0;
    ioctl(tty_fd, TIOCMGET, &mcs);
    mcs |= TIOCM_RTS;
    ioctl(tty_fd, TIOCMSET, &mcs);

    retval = tcgetattr(tty_fd, &newtio);
    if(retval != 0)
    {
        perror(DEVICE);
        exit(-1);
    }
    printf("Init 5 complete.\n");

    newtio.c_cflag &= ~CRTSCTS;

    retval = tcsetattr(tty_fd, TCSANOW, &newtio);
    if(retval != 0)
    {
        perror(DEVICE);
        exit(-1);
    }
    printf("Init 6 complete.\n");


    for(n = 5; n > 0; n--)
    {
    printf("Please enter a command: ");
    (void)fgets(buf2, 255, stdin);
    (void)write(tty_fd, buf2, strlen(buf2));
    printf("Ok. Waiting for reply\n");
    res = read(tty_fd, buf, 255);       
    printf("Read:%d START%d %d %d %d %dFINISH\n",res,buf[0],buf[1],buf[2], buf[3],
    buf[4]);              
    }

    //restore the original port settings
    tcsetattr(tty_fd, TCSANOW, &old_stdio); 

    close(tty_fd);

    return EXIT_SUCCESS; //return all good
}
