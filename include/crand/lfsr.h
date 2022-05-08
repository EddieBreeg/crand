#pragma once

/* 
Stepped 128-bit lfsr
*/

#include <stdint.h>

#if !defined(__cplusplus)
#include <stdbool.h>
#else


#endif // __cplusplus

void lfsr128_seed(uint64_t seed);
bool lfsr128_next();

#if defined(__cplusplus)

namespace crand{
    class lfsr128
    {
    private:
        uint64_t _s[2];
    public:
        lfsr128(uint64_t s1, uint64_t s2);
    };
    
    lfsr128::lfsr128(uint64_t s1, uint64_t s2)
    {
    }
    
    
}

#endif // __cplusplus
