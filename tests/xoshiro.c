#include "xoshiro.h"
#include <stdio.h>

#define N   10

int main(int argc, char const *argv[])
{
    xoshiro256_handle rng = xoshiro256_init(0);

    for (size_t i = 0; i < N; i++)
        printf("%016" PRIX64 "\n", xoshiro256_next(rng));

    xoshiro256_finish(rng);
    return 0;
}
