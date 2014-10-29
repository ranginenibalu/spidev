#include<stdio.h>
#include<time.h>

struct tim
{	
		int ti;
};

int main()
{	

	struct tim obj;
	obj.ti = (int)time(NULL);
	FILE *fp;
	fp=fopen("time.dat","ab");
	if(!(fwrite(&obj, sizeof(obj), 1, fp)))
		printf("error in writing to the file");
		
	fclose(fp);
}
