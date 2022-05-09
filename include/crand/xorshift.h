#pragma once

#include <inttypes.h>

static inline uint32_t xoshift32(uint32_t reg){
    reg ^= reg << 13;
    reg ^= reg >> 17;
    return reg ^ (reg << 5);
}

static inline uint64_t xoshift64(uint64_t reg){
    reg ^= reg << 13;
    reg ^= reg >> 7;
    return reg ^ (reg << 17);
}

#if defined(__cplusplus)

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
