#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <signal.h>
#include <ctype.h>          
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 20000
#define LENGTH 512 


void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void file_transfer(int argc, char *argv[])
{
    /* Variable Definition */
    int sockfd; 
    int nsockfd;
    char revbuf[LENGTH]; 
    int flag = 0;
    struct sockaddr_in remote_addr;

while(1)
    	
    {
    /* Get the Socket file descriptor */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        fprintf(stderr, "ERROR: Failed to obtain Socket Descriptor! (errno = %d)\n",errno);
        exit(1);
    }


     
    /* Fill the socket address struct */
    remote_addr.sin_family = AF_INET; 
    remote_addr.sin_port = htons(PORT); 
    inet_pton(AF_INET, "10.180.7.195", &remote_addr.sin_addr); 
    bzero(&(remote_addr.sin_zero), 8);

    /* Try to connect the remote */
    
   
	    if (connect(sockfd, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) == -1)
		    {
			fprintf(stderr, "ERROR: Failed to connect to the host! (errno = %d)\n",errno);
			exit(1);
		    }
	    else 
			printf("[Client] Connected to server at port %d...ok!\n", PORT);

	       

	    /* Receive File from Server */
	    printf("[Client] Receiveing file from Server and saving it as final.txt...");
	    char fr_name[8];
	    
	    if(flag == 0)
	    	strcpy(fr_name, "log_spi.dat" );
	    else 
	    	strcpy(fr_name, "log_uart.dat" );
	    	
	    
	    FILE *fr = fopen(fr_name, "a+b");
	    if(fr == NULL)
		printf("File %s Cannot be opened.\n", fr_name);
	    else
	    {
		bzero(revbuf, LENGTH); 
		int fr_block_sz = 0;
		while((fr_block_sz = recv(sockfd, revbuf, LENGTH, 0)) > 0)
		{
		    int write_sz = fwrite(revbuf, sizeof(char), fr_block_sz, fr);
		    if(write_sz < fr_block_sz)
		    {
		        error("File write failed.\n");
		    }
		    bzero(revbuf, LENGTH);
		    if (fr_block_sz == 0 || fr_block_sz != 512) 
		    {
		        break;
		    }
		}
		if(fr_block_sz < 0)
		{
		    if (errno == EAGAIN)
		    {
		        printf("recv() timed out.\n");
		    }
		    else
		    {
		        fprintf(stderr, "recv() failed due to errno = %d\n", errno);
		    }
		}
		printf("Ok received from server!\n");
		fclose(fr);
	    }
	    
	    if(flag == 0)
		    	flag = 1;
		    else
		    	flag = 0;
	    
	    sleep(1);
    
    close (sockfd);
    printf("[Client] Connection lost.\n");
    sleep(3);
    }
    return (0);
}
