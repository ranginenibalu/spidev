#include<stdio.h>

#include<iostream>
#include<math.h>
#include<string.h>
#include<stdlib.h>
using namespace std;

char START[5] = "5120";
char len[5];
char payload[15];


void accept_bytes(char * x)
{
	int i,j=0;
	char st[4];
	
	for(i=0;i<4;i++)
	{	st[i] = x[i];
		j++;
	}
	//cout<<"start is:"<<
	
	if(strcmp(st,START)==0 )
	{
		for(i=0;i<4;i++)
		{
			len[i]=x[j];
			j++;
		}
		int n=atoi(len);
		cout<<"len:"<<n<<endl;
		for(i=0;i<n;i++,j++)
		{
			payload[i]=x[j];
		}
		
		//for(i=0;i<n;i++)
		//{
			cout<<"payload is:"<<payload<<endl;	
		//}
	}
	else
		cout<<"error"<<endl;
//	return 0;
}
		
		

int main()
{	char data[20]="5120000512345";
 	accept_bytes(data);
 	return 0;
}




