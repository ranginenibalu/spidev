#include <pthread.h>

#include <iostream>
using namespace std;

void task1() { 
    // do stuff
}

void task2() { 
    // do stuff
}

int main (int argc, char ** argv) {
     
    thread thread_1 = thread(task1);
    thread thread_2 = thread(task2);

    // do other stuff
    thread_2.join();
    thread_1.join();
    return 0;
}
