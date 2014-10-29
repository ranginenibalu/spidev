#include <pthread.h>

#include <iostream>

using namespace std ;

void* function1(void* arg);


int main( void )
{

   pthread_t  t1, t2 ;

   string msg1 ("hello\n")  ;
   string msg2 ("world")  ;

   int create1 = pthread_create( &t1, NULL, function1,reinterpret_cast<void*>(&msg1));
    if (create1 != 0) cout << "error" ;
    
   int create2 = pthread_create( &t1, NULL, function1,reinterpret_cast<void*>(&msg2));
    if (create2 != 0) cout << "error" ;
   pthread_join(t1,NULL) ;
   pthread_join(t1,NULL) ;

   return 0;
}

void* function1(void* arg)
{
    cout << *(reinterpret_cast<string*>(arg)) << endl ;
    sleep(3);
    return 0;
}
