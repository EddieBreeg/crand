#pragma once

#include <stdio.h>

#define STYLE_DEFAULT   "\033[0m"
#define STYLE_ERROR     "\033[31;1m"
#define STYLE_OK        "\033[32;1m"

#define STR_FMT_ERROR(str)   STYLE_ERROR str STYLE_DEFAULT
#define STR_FMT_OK(str)      STYLE_OK str STYLE_DEFAULT


#define TEST_HEADER(name)   "[ " name " ]\t\t"

#if defined(__cplusplus)

#include <crand/prng.hpp>

template<typename T>
int run_rng_test(crand::prng<T>& rng, T (*c_interface)(), T *expected, int n)
{
    for (int i = 0; i < n; i++)
    {
        if(rng() != expected[i] || (c_interface && c_interface() != expected[i])) return i;
    }
    return -1;
}

template<typename cprng>
int run_cprng_test(cprng& rng, void (*c_interface)(void *block), uint8_t *expected){
    constexpr int n = (int)cprng::blockSize();
    uint8_t block[n];
    rng(block);
    for (int i = 0; i < n; i++)
        if(block[i] != expected[i]) return i;
    if (c_interface)
    {
        c_interface(block);
        for (int i = 0; i < n; i++)
            if(block[i] != expected[i]) return i;
    }
    return -1;
}

#endif // __cplusplus
