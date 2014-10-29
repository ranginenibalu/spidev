#include<stdio.h>
//#include <fstream>
//#include<iostream>
#include<math.h>
#include<string.h>
#include<stdlib.h>

//using namespace std;

struct sensor_info
{
	short int net_id; //2 bytes
	char addr[9]; //8 bytes
	unsigned char sensor_id; //1 byte
	char sensor_val[7]; // 6 bytes
	int timestamp; //4 bytes
	short int lqi; //2 bytes
};

int main(int argc, char * argv[] )
{
	//fstream fp;
	//fp.open("store1.dat", ios::in|ios::binary);
	int i;
	struct sensor_info si;
	
	FILE *fp;
	fp=fopen(argv[1],"r+b");
	while((fread(&si, sizeof(si), 1, fp)))
		//printf("error in writing to the file");
		
	
	//while(fp.read((char *)&si, sizeof(struct sensor_info)))
	{
	
		printf("netid:%x\n",si.net_id);
	
		printf("addr: ");
		for(i=0;i<8;i++)
			printf("%x ",si.addr[i]);
		
		printf("sensor_id:%x\n",si.sensor_id);
	
		printf("sensor_value: ");
		for(i=0;i<6;i++)
			printf("%x ",si.sensor_val[i]);
		
		printf("timestamp:%x\n",si.timestamp);
	
		printf("lqi:%x\n\n",si.lqi);
	
	}
	fclose(fp);
	return 0;
}
