#include<stdio.h>
#include<time.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

#define LEN 21




struct sensor_info
{
	short int net_id; //2 bytes
	char addr[9]; //8 bytes
	unsigned char sensor_id; //1 byte
	char sensor_val[7]; // 6 bytes
	int timestamp; //4 bytes
	short int lqi; //2 bytes
};

void accept_bytes(char *);

short int arr[LEN];
short int START = 85;
char len[5];
short int payload[LEN];
int flag=0;

void write_file(short int * payload, char * file); 

void convert( char * rx, char * file)
{	
	
	int i,j, k;
	
	for(i=0;i<LEN;i++)
		arr[i] = (short int)rx[i];
	printf("\n");
	for(i=0;i<LEN;i++)
		printf("%x ", arr[i]);
	printf("\n");
		
	accept_bytes(file);
}


void accept_bytes(char * file)
{
	int i,j=0,n;
	int temp;
	//char st[4];
	
	
	for(j=0;j<LEN;j++)
	{
		flag=0;
		//i = 0;
		if(arr[j] == START )
			flag=1;
		
		/*for(i=0;i<LEN-1;i++,j++)
		{	if(START[i]!=x[j])
				break;
		}
		//cout<<"start is:"<<*/
	
		if(flag==1)
		{
			/*for(i=0;i<4;i++)
			{
				len[i]=(char)x[j];
				j++;
			}*/
			//n=atoi(len);
			n=arr[++j];
			printf("len:%d\n",n);
			j++;
			j++;
			temp = arr[j];
			arr[j] = arr[j+1];
			arr[j+1] = temp;
			for(i=0;i<n;i++,j++)
			{
				payload[i]=arr[j];
			}
			//payload[i]='\0';
			
			printf("payload is: ");
			for(i=0;i<n;i++)
			{
				printf("%x ",payload[i]);
				//j--;
					
			}
			printf("\n%s\n", file);
			write_file(payload, file);
		}
		else
			{}//printf("error");}
	}
//	return 0;
}

void write_file(short int * payload, char * file)
{
	FILE *fp;
	int i, j=0;
	struct sensor_info si;
	short int x;
	short int n;
	
	//net_id
	//char s[2];
	si.net_id=(payload[j]*0x100) + (payload[j+1]);
	j++;
	//s[0]=payload[j++];
	//s[1]=payload[j++];
	//n=atoi(s);
	//si.net_id=n;
	j++;
	
	//addr
	for(i=0;i<8;i++,j++)
		si.addr[i]=payload[j];
	si.addr[i]='\0';
	
	//sensor_id
	si.sensor_id=payload[j++];
	
	//sensor_val
	for(i=0;i<6;i++,j++)
		si.sensor_val[i]=payload[j];
	si.sensor_val[i]='\0';
		
	//timestamp
	j=j+2;
	si.timestamp=(int)time(NULL);
	
	//j++;
	
	//x[0]=payload[j++];
	//x[1]=payload[j++];
	//x[2]='\0';
	//si.timestamp=atoi(x);
	
	
	//lqi
	si.lqi=(payload[j]<<8) | (payload[j+1]);
	
	/*x[0]=payload[j++];
	x[1]=payload[j++];
	x[2]='\0';
	si.lqi=atoi(x);*/
	
	/*fstream fp;
	fp.open("store1.dat",ios::out|ios::app|ios::binary);
	if(!(fp.write((char *) &si, sizeof(struct sensor_info))))
	{
		printf("error in writing to the file");
	} */
	
	fp=fopen(file,"a+b");
	if(!(fwrite(&si, sizeof(si), 1, fp)))
		printf("error in writing to the file");
	else
		printf("succesful writing to %s\n", file);	
	fclose(fp);
	
	
	//printing
	printf("netid:%x\n",si.net_id);
	
	printf("addr: ");
	for(i=0;i<8;i++)
		printf("%x ",si.addr[i]);
		
	printf("sensor_id:%x\n",si.sensor_id);
	
	printf("sensor_value: ");
	for(i=0;i<6;i++)
		printf("%x ",si.sensor_val[i]);
		
	printf("timestamp:%d\n",si.timestamp);
	
	printf("lqi:%d\n\n",si.lqi);
	
}
	
	
	
	
		
		

/*int main()
{	
	char data[100]="5120002112345678912345678912351200021987654321987654321987";
	data[58] = '\0';
 	accept_bytes(data);
 	return 0;
}*/




