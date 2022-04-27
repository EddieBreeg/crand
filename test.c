#include "rand.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    unsigned char foo[16] = {};
    long n = randomize(foo, 16);
    if(n == -1){
        printf("Couldn't generate random bytes\n");
        return 1;
    }
    for (int i = 0; i < 16; i++)
        printf("%02x ", foo[i]);
    printf("\n");    
    return 0;
}
