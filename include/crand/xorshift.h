#pragma once

#include <inttypes.h>

#ifdef __cplusplus
extern "C"{
#endif

// Seed the xorshift32 PRNG. Any seed is allowed
void xorshift32_seed(uint64_t seed);
// Seed the xorshift64 PRNG. Any seed is allowed
void xorshift64_seed(uint64_t seed);

// Generates the next value in the sequence
uint32_t xorshift32_next();
// Generates the next value in the sequence
uint64_t xorshift64_next();

#if defined(__cplusplus)
}
#include  "crand/prng.hpp"

namespace crand{
    // Class for the xorshift32 generator
    class xorshift32: public prng<uint32_t>
    {
    private:
        // internal state
        uint32_t _s;
    public:
        xorshift32(uint64_t seed);
        // Generates the next value in the sequence
        virtual result_type operator()();
        static constexpr result_type min() { return 1; };
        static constexpr result_type max() { return UINT32_MAX; };
        /* Sets the seed for the generator */
        void seed(uint64_t seed);
    };

    // Class for the xorshift64 generator
    class xorshift64: public prng<uint64_t>
    {
    private:
        // internal state
        uint64_t _s;
    public:
        xorshift64(uint64_t seed);
        // Generates the next value in the sequence
        virtual result_type operator()();
        /* Sets the seed for the generator */
        void seed(uint64_t seed);
        static constexpr result_type min() { return 1; };
        static constexpr result_type max() { return UINT64_MAX; };
    };
}

#endif // __cplusplus
