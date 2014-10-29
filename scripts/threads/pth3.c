#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* print_thread_num(void *index);

int main(int argc, char** argv) {

    int i;
    pthread_t threads[3];

    for (i = 0; i < 3; i++) {
        void *index = &i;
        printf("Creating thread %d\n", i);
        pthread_create(&threads[i], NULL, print_thread_num, index);
    }
    pthread_exit(NULL);
}

void* print_thread_num(void *index) {
    int i = *(int*)index;
    printf("I am the thread at index %d\n", i);
    pthread_exit(NULL);
}
