#include "crand/lfsr.h"

typedef struct
{
    uint64_t _s[2];
} lfsr128_state;

lfsr128_state reg;

static inline uint64_t splitmix64(uint64_t* state) {
	uint64_t result = (*state + 0x9E3779B97f4A7C15);
	result = (result ^ (result >> 30)) * 0xBF58476D1CE4E5B9;
	result = (result ^ (result >> 27)) * 0x94D049BB133111EB;
	return result ^ (result >> 31);
}

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