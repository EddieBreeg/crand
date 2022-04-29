#pragma once
#include <inttypes.h>

#ifndef __cplusplus

struct xoshiro256_s;

typedef struct xoshiro256_s* xoshiro256_handle;

xoshiro256_handle xoshiro256_init(uint64_t seed);
void xoshiro256_reseed(xoshiro256_handle rng, uint64_t seed);
uint64_t xoshiro256_next(xoshiro256_handle rng);
void xoshiro256_finish(xoshiro256_handle rng);

#else


#endif