#include "rand.h"
#include <stdio.h>

#define N   512

int main(int argc, char const *argv[])
{
    unsigned char foo[N] = {0};
    long n = randomize(foo, N);
    if(n == -1){
        printf("Couldn't generate random bytes\n");
        return 1;
    }
    for (int i = 0; i < N; i++)
        printf("%02x ", foo[i]);
    printf("\n");    
    return 0;
}
