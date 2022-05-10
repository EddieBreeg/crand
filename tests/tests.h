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

#endif // __cplusplus
