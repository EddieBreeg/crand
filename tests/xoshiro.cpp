#include <iostream>
#include <crand/crand.h>

#define N   10


int main(int argc, char const *argv[])
{
    crand::xoshiro256 rng(0);
    xoshiro256_seed(0);

    for (size_t i = 0; i < N; i++)
        printf("%016" PRIX64 "\t%016" PRIX64 "\n", rng(), xoshiro256_next());

    return 0;
}
