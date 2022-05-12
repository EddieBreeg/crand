#include "crand/xorshift.h"
#include "crand/splitmix64.h"

namespace crand
{
    xorshift32::xorshift32(uint64_t seed){
        _s = (uint32_t)splitmix64(&seed);
    }
    void xorshift32::seed(uint64_t seed){
        _s = (uint32_t)splitmix64(&seed);
    }

    xorshift64::xorshift64(uint64_t seed){
        _s = splitmix64(&seed);
    }
    void xorshift64::seed(uint64_t seed){
        _s = splitmix64(&seed);
    }
    xorshift32::result_type xorshift32::operator()(){
        _s ^= _s << 13;
        _s ^= _s >> 17;
        return _s ^= _s << 5;
    }
    xorshift64::result_type xorshift64::operator()(){
        _s ^= _s << 13;
        _s ^= _s >> 7;
        return _s ^= _s << 17;
    }
} // namespace crand
