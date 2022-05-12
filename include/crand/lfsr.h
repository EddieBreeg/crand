#pragma once

/* 
128-bit linear feedback shift register
*/

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

// Seeds the lfsr PRNG. Any seed is allowed.
void lfsr128_seed(uint64_t seed);
// Generates the next value in the sequence
unsigned char lfsr128_next();

#if defined(__cplusplus)
}
#include "prng.hpp"

namespace crand{
    /* Class for the lfsr128 generator */
    class lfsr128: public prng<unsigned char>
    {
    private:
        /* Internal state */
        uint64_t _s[2];
    public:
        lfsr128(uint64_t seed);
        /* Sets the seed for the generator */
        void seed(uint64_t seed);
        static constexpr result_type min() { return 0; }
        static constexpr result_type max() { return 1; }
        // Generates the next bit in the sequence
        result_type operator()() override;
    };
}

#endif // __cplusplus
