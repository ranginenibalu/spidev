#include <pthread.h>
#include <stdio.h>
#include<iostream>

using namespace std;

#define NUM_THREADS     5

void *PrintHello(void *threadid)
{
   long tid;
   tid = (long)threadid;
   cout<<"Hello World! It's me, thread "<< tid << "\n";
   pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
   pthread_t threads[NUM_THREADS];
   
   int rc;
   long t;
   
   for(t=0; t<NUM_THREADS; t++){
      cout<<"In main: creating thread "<< t << "\n";
      rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
      /*if (rc){
         cout<<"ERROR; return code from pthread_create() is "<< rc << "\n";
         exit(-1);

      }*/
     
     }
   pthread_exit(NULL);
}

   /* Last thing that main() should do */


