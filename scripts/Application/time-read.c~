#include<stdio.h>
#include<time.h>

struct tim
{	
		short int ti;
};

int main()
{	

	struct tim obj;
	FILE *fp;
	fp=fopen("time.dat","a+b");
	while((fread(&obj, sizeof(obj), 1, fp)))
		printf("\nThe time is:  %d ",obj.ti);
			
		
		fclose(fp);
}
