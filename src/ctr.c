#include "aes/aes.h"
#include <inttypes.h>

uint8_t key_schedule[240];
uint64_t state[2];

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

void ctr_aes256_seed(const uint8_t key[32], uint64_t nonce)
{
    state[0] = 0;
    #if __LITTLE_ENDIAN == __BYTE_ORDER
    state[1] = nonce;
    #else
    state[1] = lendian64(nonce);
    #endif
    aes256_set_key((aes256*)key_schedule, key);
}
void ctr_aes256_next(void *output)
{
    aes256_encrypt_block(state, output, (aes256*)key_schedule);
    #if __LITTLE_ENDIAN == __BYTE_ORDER
    state[0]++;
    #else
    state[0] = lendian64(lendian64(_s[0]) + 1);
    #endif
}
uint64_t ctr_aes256_get_counter()
{
    #if __LITTLE_ENDIAN == __BYTE_ORDER
    return state[0];
    #else
    return lendian64(state[0]);
    #endif
}
uint64_t ctr_aes_get_nonce()
{
    #if __LITTLE_ENDIAN == __BYTE_ORDER
    return state[1];
    #else
    return lendian64(state[1]);
    #endif
}
void ctr_aes256_set_counter(uint64_t c)
{
    #if __LITTLE_ENDIAN == __BYTE_ORDER
    state[0] = c;
    #else
    state[0] = lendian64(c);
    #endif
}
void ctr_aes_set_nonce(uint64_t nonce)
{
    #if __LITTLE_ENDIAN == __BYTE_ORDER
    state[1] = nonce;
    #else
    state[1] = lendian64(nonce);
    #endif
}
