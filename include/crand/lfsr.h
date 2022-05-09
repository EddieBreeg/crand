#pragma once

/* 
Stepped 128-bit lfsr
*/

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#else
#include <stdbool.h>
#endif


void lfsr128_seed(uint64_t seed);
bool lfsr128_next();

#if defined(__cplusplus)
}
#include "prng.hpp"

namespace crand{
    class lfsr128: public prng<unsigned char>
    {
    private:
        uint64_t _s[2];
    public:
        lfsr128(uint64_t seed);
        static constexpr result_type min() { return 0; }
        static constexpr result_type max() { return 1; }
        result_type operator()() override;
    };
}

#endif // __cplusplus
