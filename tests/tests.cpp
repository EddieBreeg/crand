#include <crand/crand.h>
#include <stdio.h>
#include "tests.h"
#include "test_vectors.h"

int main(int argc, char const *argv[])
{
    printf("\tcrand version %d.%d.%d\t\n\n=================================\n\n"
        , CRAND_VERSION_MAJOR, CRAND_VERSION_MINOR, CRAND_VERSION_PATCH);
    int r;
    uint64_t s=0;


    printf(TEST_HEADER("SplitMix64"));
    if(splitmix64(&s) != 0xe220a8397b1dcdaf || splitmix64(&s) != 0x6e789e6aa1b965f4)
        printf(STR_FMT_ERROR("FAILED\n"));
    else printf(STR_FMT_OK("OK\n"));
    
    crand::lfsr128 lfsr(0);
    lfsr128_seed(0);
    printf(TEST_HEADER("LFSR128"));
    if(r=run_rng_test<unsigned char>(lfsr, lfsr128_next, lfsr_v, 256) != -1)
        printf(STR_FMT_ERROR("FAILED\n"));
    else printf(STR_FMT_OK("OK\n"));


    return 0;
}
