#include "crand/ctr.h"
#include "crand/aes/endian.h"

#if __BYTE_ORDER != __LITTLE_ENDIAN

static inline uint64_t lendian64(uint64_t x){
    uint8_t b[] = {
        (uint8_t)x,
        (uint8_t)(x >> 8),
        (uint8_t)(x >> 16),
        (uint8_t)(x >> 24),
        (uint8_t)(x >> 32),
        (uint8_t)(x >> 40),
        (uint8_t)(x >> 48),
        (uint8_t)(x >> 56),
    };
    return *(uint64_t*)b;
}
#endif

namespace crand{
    ctr_aes256::ctr_aes256(const uint8_t key[32], uint64_t nonce): _aes(key)
    {
        #if __BYTE_ORDER != __LITTLE_ENDIAN
            _s[1] = lendian64(nonce);
        #else
            _s[1] = nonce;
        #endif
    }    
    uint64_t ctr_aes256::counter() const{
        #if __LITTLE_ENDIAN == __BYTE_ORDER
        return _s[0];
        #else
        return lendian64(state[0]);
        #endif
    }
    void ctr_aes256::counter(uint64_t c){
        #if __LITTLE_ENDIAN == __BYTE_ORDER
        _s[0] = c;
        #else
        _s[0] = lendian64(c);
        #endif
    }
    uint64_t ctr_aes256::nonce() const{
        #if __LITTLE_ENDIAN == __BYTE_ORDER
        return _s[1];
        #else
        return lendian64(state[1]);
        #endif
    }
    void ctr_aes256::nonce(uint64_t nonce){
        #if __LITTLE_ENDIAN == __BYTE_ORDER
        _s[1] = nonce;
        #else
        _s[1] = lendian64(nonce);
        #endif
    }
    void ctr_aes256::operator()(void *output)
    {
        _aes.encrypt_block(_s, output);
        #if __LITTLE_ENDIAN == __BYTE_ORDER
        _s[0]++;
        #else
        _s[0] = lendian64(lendian64(_s[0]) + 1);
        #endif
    }

}