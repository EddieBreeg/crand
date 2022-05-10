#include "crand/splitmix64.h"
#include <stdio.h>
#include "./tests.h"

int main(int argc, char const *argv[])
{
    uint64_t x = 0, y, z;
    y = splitmix64(&x);
    z = splitmix64(&x);
    printf(STR_FMT_OK("%016lx%016lx\n"), z, y);
    
    return 0;
}
