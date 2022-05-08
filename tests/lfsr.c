#include "crand/crand.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    lfsr128_seed(0);

    for (int i = 0; i < 128; i++)
        printf("%i", lfsr128_next());
    printf("\n");
    return 0;
}
