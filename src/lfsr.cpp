#include <crand/crand.h>

namespace crand
{
    lfsr128::lfsr128(uint64_t seed)
    {
        _s[0] = splitmix64(&seed);
        _s[1] = splitmix64(&seed);
    }
    lfsr128::result_type lfsr128::operator()()
    {
        bool out = _s[0] & 1;
        bool fbk = (_s[0] ^ (_s[0]>>1) ^ (_s[0]>>2) ^ (_s[0]>>7)) & 1;
        _s[0] = (_s[0]>>1) | (_s[1] << 63);
        _s[1] = (_s[1]>>1) | ((uint64_t)fbk << 63);
        return out;
    }
} // namespace crand
