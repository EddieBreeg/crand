/* xoshiro256** algorithm
All-purpose not cryptographic generator, with a 256-bit state
 */
#pragma once
#include <inttypes.h>

#ifdef __cplusplus
extern "C"{
#endif


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
}
#include "prng.hpp"

namespace crand
{
   /* Class for the xoshiro256** PRNG */
   class xoshiro256: public prng<uint64_t>
   {
   private:
      /* Internal state */
      uint64_t _s[4];
   public:
      /* Inits the generator, any key is ok */
      xoshiro256(uint64_t seed);
      static constexpr result_type min() { return 0; }
      static constexpr result_type max() { return UINT64_MAX; }
      // Generates the next value in the sequence
      result_type operator()() override;
      // Jump method, equivalent to 2^128 updates
      void jump();
      // Jump method, equivalent to 2^192 updates
      void long_jump();
      /* Sets the seed for the generator */
      void seed(uint64_t seed);
   };   
} // namespace crand


#endif