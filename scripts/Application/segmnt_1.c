#include<stdio.h>


#include<math.h>
#include<string.h>
#include<stdlib.h>

char START[5] = "5120";
char len[5];
char payload[15];


void accept_bytes(char * x)
{
	int i,j=0;
	char st[4];
	
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
		//}
	}
	else
		printf("error");
//	return 0;
}
		
		

int main()
{	char data[20]="5120000512345";
 	accept_bytes(data);
 	return 0;
}




