#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>



struct sensor_info
{
	short int net_id; //2 bytes
	char addr[9]; //8 bytes
	unsigned char sensor_id; //1 byte
	char sensor_val[7]; // 6 bytes
	short int timestamp; //2 bytes
	short int lqi; //2 bytes
};

char START[5] = "5120";
char len[5];
char payload[15];

void write_file(char * payload); 
void accept_bytes(char * x)
{
	int i,j=0;
	char st[4];
	
	while(x[j]!='\0')
	{
		for(i=0;i<4;i++)
		{	if(START[i]!=x[j])
				break;
		}
		//cout<<"start is:"<<
	
		if(i==4)
		{
			for(i=0;i<4;i++)
			{
				len[i]=x[j];
				j++;
			}
			int n=atoi(len);
			printf("len:%d\n",n);
			for(i=0;i<n;i++,j++)
			{
				payload[i]=x[j];
			}
		
			//for(i=0;i<n;i++)
			//{
				printf("payload is:%d\n",payload);
				write_file(payload);	
			//}
		}
		else
			printf("error");
	}
//	return 0;
}

void write_file(char * payload)
{
	int i, j=0;
	sensor_info *si;
	char x[2];
	short int n;
	
	//net_id
	char s[2];
	s[0]=payload[j++];
	s[1]=payload[j++];
	n=atoi(s);
	si->net_id=n;
	
	
	//addr
	for(i=0;i<8;i++)
		si->addr[i]=payload[j++];
	si->addr[i]='\0';
	
	//sensor_id
	si->sensor_id=payload[j++];
	
	for(i=0;i<6;i++,j++)
		si->sensor_val[i]=payload[j];
	si->sensor_val[i]='\0';
		
	
	x[0]=payload[j++];
	x[1]=payload[j++];
	si->timestamp=atoi(x);
	
	x[0]=payload[j++];
	x[1]=payload[j++];
	si->lqi=atoi(x);
	
	/*fstream fp;
	fp.open("store1.dat",ios::out|ios::app|ios::binary);
	if(!(fp.write((char *) &si, sizeof(struct sensor_info))))
	{
		printf("error in writing to the file");
	} */
	
	FILE *fp;
	fp=fopen("store1.dat","r+b");
	if(!(fwrite(si, sizeof(*si), 1, fp)))
		printf("error in writing to the file");
		
	fclose(fp);
	
	/*printf("netid:%d\n",si.net_id);
	printf("addr:%s\n",si.addr);
	printf("sensor_id:%d\n",si.sensor_id);
	printf("sensor_val:%s\n",si.sensor_val);
	printf("timestamp:%d\n",si.timestamp);
	printf("lqi:%d\n",si.lqi);*/
	
}
	
	
	
	
		
		

int main()
{	
	char data[100]="5120002112345678912345678912354376512000512345";
 	accept_bytes(data);
 	return 0;
}




