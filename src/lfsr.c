#include "crand/lfsr.h"

#include "crand/splitmix64.h"

typedef struct
{
    uint64_t _s[2];
} lfsr128_state;

lfsr128_state reg;


void lfsr128_seed(uint64_t seed){
    reg._s[0] = splitmix64(&seed);
    reg._s[1] = splitmix64(&seed);
}

bool lfsr128_next(){
    bool out = reg._s[0] & 1;
    bool fbk = (reg._s[0] ^ (reg._s[0]>>1) ^ (reg._s[0]>>2) ^ (reg._s[0]>>7)) & 1;
    reg._s[0] = (reg._s[0]>>1) | (reg._s[1] << 63);
    reg._s[1] = (reg._s[1]>>1) | ((uint64_t)fbk << 63);
    return out;
}