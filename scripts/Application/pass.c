#include <stdio.h>
#include <time.h>

int main(void) {
    printf("Timestamp: %d\n",(int)time(NULL));
    
    printf("Sizeof = %d", sizeof(int) );
    return 0;
}
