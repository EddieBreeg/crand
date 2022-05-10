#pragma once

#include <inttypes.h>

#ifdef __cplusplus
extern "C"{
#endif

void xorshift32_seed(uint64_t seed);
void xorshift64_seed(uint64_t seed);

uint32_t xorshift32_next();
uint64_t xorshift64_next();

#if defined(__cplusplus)
}
#include  "crand/prng.hpp"

namespace crand{
    class xorshift32: public prng<uint32_t>
    {
    private:
        uint32_t _s;
    public:
        xorshift32(uint64_t seed);
        virtual result_type operator()();
        static constexpr result_type min() { return 1; };
        static constexpr result_type max() { return UINT32_MAX; };
    };

    class xorshift64: public prng<uint64_t>
    {
    private:
        uint64_t _s;
    public:
        xorshift64(uint64_t seed);
        virtual result_type operator()();
        static constexpr result_type min() { return 1; };
        static constexpr result_type max() { return UINT64_MAX; };
    };
}

#endif // __cplusplus
