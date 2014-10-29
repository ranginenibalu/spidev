#include<stdio.h>

int flag[5]={0,0,0,0,0}, count=0;

void print(void * j)
{
	int * i;
	i=(int *)j;
	printf("thraed %d running\n", *i);
	flag[i]=0;
	count--;
}
