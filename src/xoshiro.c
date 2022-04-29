#include "xoshiro.h"
#include <stdlib.h>

#define rol64(x, k)     (((x) << (k)) | ((x) >> (64 - (k))))

typedef struct xoshiro256_s
{
    uint64_t s[4];
} xoshiro256_s;

static inline uint64_t splitmix64(uint64_t x) {
	uint64_t z = (x += 0x9e3779b97f4a7c15);
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
	return z ^ (z >> 31);
}

xoshiro256_handle xoshiro256_init(uint64_t seed)
{
	xoshiro256_handle rng = malloc(sizeof(*rng));
	if(!rng) return NULL;
	rng->s[0] = seed = splitmix64(seed);
	rng->s[1] = seed = splitmix64(seed);
	rng->s[2] = seed = splitmix64(seed);
	rng->s[3]		 = splitmix64(seed);

	return rng;
}
void xoshiro256_reseed(xoshiro256_handle rng, uint64_t seed)
{
	rng->s[0] = seed = splitmix64(seed);
	rng->s[1] = seed = splitmix64(seed);
	rng->s[2] = seed = splitmix64(seed);
	rng->s[3]		 = splitmix64(seed);
}
uint64_t xoshiro256_next(xoshiro256_handle rng) 
{
	const uint64_t result = rol64(rng->s[1] * 5, 7) * 9;

	const uint64_t t = rng->s[1] << 17;

	rng->s[2] ^= rng->s[0];
	rng->s[3] ^= rng->s[1];
	rng->s[1] ^= rng->s[2];
	rng->s[0] ^= rng->s[3];

	rng->s[2] ^= t;

	rng->s[3] = rol64(rng->s[3], 45);

	return result;
}
void xoshiro256_finish(xoshiro256_handle rng) { free(rng); }