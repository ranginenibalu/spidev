#include<stdio.h>
#include <fstream>
#include<iostream>
#include<math.h>
#include<string.h>
#include<stdlib.h>

using namespace std;

struct sensor_info
{
	short int net_id; //2 bytes
	char addr[9]; //8 bytes
	unsigned char sensor_id; //1 byte
	char sensor_val[7]; // 6 bytes
	short int timestamp; //2 bytes
	short int lqi; //2 bytes
};

int main()
{
	//fstream fp;
	//fp.open("store1.dat", ios::in|ios::binary);
	sensor_info si;
	
	FILE *fp;
	fp=fopen("store1.dat","r+b");
	while((fread(&si, sizeof(si), 1, fp)))
		//printf("error in writing to the file");
		
	
	//while(fp.read((char *)&si, sizeof(struct sensor_info)))
	{
	
		printf("netid:%d\n",si.net_id);
		printf("addr:%s\n",si.addr);
		printf("sensor_id:%c\n",si.sensor_id);
		printf("sensor_val:%s\n",si.sensor_val);
		printf("timestamp:%d\n",si.timestamp);
		printf("lqi:%d\n",si.lqi);
	}
	fclose(fp);
	return 0;
}
