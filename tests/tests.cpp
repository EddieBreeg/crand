#include <crand/crand.h>
#include <crand/xorshift.h>
#include <stdio.h>
#include "tests.h"
#include "test_vectors.h"

chacha20_state *c_chacha;

void chacha_block(void *block) { chacha20_block(c_chacha, block); }

int main(int argc, char const *argv[])
{
    crand::crand_version_t version = crand::crand_get_version();
    printf("\tcrand version %d.%d.%d\t\n\n=================================\n\n"
        , version.major, version.minor, version.patch);
    int r;
    uint64_t s=0;


    printf(TEST_HEADER("SplitMix64"));
    if(splitmix64(&s) != 0xe220a8397b1dcdaf || splitmix64(&s) != 0x6e789e6aa1b965f4)
        printf(STR_FMT_ERROR("FAILED\n"));
    else printf(STR_FMT_OK("OK\n"));
    
    crand::lfsr128 lfsr(0);
    lfsr128_seed(0);
    printf(TEST_HEADER("LFSR128   "));
    if(r=run_prng_test<unsigned char>(lfsr, lfsr128_next, lfsr_v, 256) != -1)
        printf(STR_FMT_ERROR("FAILED\n"));
    else printf(STR_FMT_OK("OK\n"));

    uint8_t k[32] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
    
    crand::ctr_aes256 ctraes(k, 0);
    ctr_aes256_seed(k, 0);
    
    printf(TEST_HEADER("CTR AES256"));
    if(r=run_cprng_test(ctraes, ctr_aes256_next, aes_v) != -1)
        printf(STR_FMT_ERROR("FAILED\n"));
    else printf(STR_FMT_OK("OK\n"));

    printf(TEST_HEADER("xoshift32 "));
    crand::xorshift32 xos32(0);
    xorshift32_seed(0);
    if(run_prng_test(xos32, xorshift32_next, xorshift32_v, 8) != -1)
        printf(STR_FMT_ERROR("FAILED\n"));
    else printf(STR_FMT_OK("OK\n"));

    printf(TEST_HEADER("xoshift64 "));
    crand::xorshift64 xos64(0);
    xorshift64_seed(0);
    if(run_prng_test(xos64, xorshift64_next, xorshift64_v, 8) != -1)
        printf(STR_FMT_ERROR("FAILED\n"));
    else printf(STR_FMT_OK("OK\n"));

    printf(TEST_HEADER("xoshiro256"));
    crand::xoshiro256 xoshiro(0);
    xoshiro256_seed(0);
    if(run_prng_test(xoshiro, xoshiro256_next, xoshiro_v, 10) != -1)
        printf(STR_FMT_ERROR("FAILED\n"));
    else printf(STR_FMT_OK("OK\n"));


    printf(TEST_HEADER("ChaCha20  "));
    uint8_t k2[32] = {0};
    crand::chacha20 chacha(k2, k2);
    c_chacha = chacha20_init(k2, k2, 0);
    if(run_cprng_test(chacha, chacha_block, chacha_v) != -1)
        printf(STR_FMT_ERROR("FAILED\n"));
    else printf(STR_FMT_OK("OK\n"));
    chacha20_clean(c_chacha);

    return 0;
}
