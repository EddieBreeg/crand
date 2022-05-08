/* xoshiro256** algorithm
All-purpose not cryptographic generator, with a 256-bit state
 */
#pragma once
#include <inttypes.h>


// seeds the xoshiro256 PRNG
void xoshiro256_seed(uint64_t seed);
// computes the next value in the sequence
uint64_t xoshiro256_next(void);
/* This is the jump function for the generator. It is equivalent
   to 2^128 calls to next(); it can be used to generate 2^128
   non-overlapping subsequences for parallel computations. */
void xoshiro256_jump(void);
/* This is the long-jump function for the generator. It is equivalent to
   2^192 calls to next(); it can be used to generate 2^64 starting points,
   from each of which jump() will generate 2^64 non-overlapping
   subsequences for parallel distributed computations. */
void xoshiro256_long_jump(void);

#ifdef __cplusplus

#endif