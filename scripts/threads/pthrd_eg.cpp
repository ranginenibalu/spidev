#include <pthread.h>
#include <unistd.h>
#include <iostream>


using namespace std ;

void  * function1(void * argument);
void  * function2(void * argument);

int main( void )
{
    pthread_t t1, t2 ; // declare 2 threads.
    pthread_create( &t1, NULL, function1, NULL); // create a thread running function1
    pthread_create( &t2, NULL, function2,NULL); // create a thread running function2

    // Because all created threads are terminated when main() finishes, we have
    // to give the threads some time to finish. Unfortunately for function1, main()
    // will give only 1 second, but function1 needs at least 2 seconds. So function1 will
    // probably be terminated before it can finish. This is a BAD way to manage threads.
   // sleep(2);
    
    /*pthread_exit(NULL);
    pthread_join( t1, NULL);
    pthread_join( t2, NULL);	
    cout<<"after the thread has been executed\n ";   These three lines can be used to wait for the threads to be executed fully .
    */ 
    return 0;
}

void * function1(void * argument)
{
	    cout << " hello " << endl ;
	   
	   
	    sleep(4); // fall alseep here for 2 seconds...
	    
	    cout<<"after the sleep of 4 secs\n";
	    return 0;
	
    
}

void * function2(void * argument)
{

	    cout << " world "  << endl ;
            cout<<"the pgm is in function2 \n";
	

	    return 0;
     
}

