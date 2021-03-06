#include "crand/ctr.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    uint8_t k[32];
    for (int i = 0; i < 32; i++) k[i] = i;
    uint8_t block[16] = {0};
    
    crand::ctr_aes256 rng(k, 0);

    for (int i = 0; i < 3; i++)
    {
        rng(block);

        for (int i = 0; i < 16; i++)
            printf("0x%02x ", block[i]);
        printf("\n");    
    }
    return 0;
}
