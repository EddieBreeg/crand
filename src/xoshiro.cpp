#include "crand/xoshiro.h"
#include "crand/splitmix64.h"

#define rotl(x, k) ((x) << (k)) | ((x) >> (64 - (k)))

namespace crand
{
   xoshiro256::xoshiro256(uint64_t seed){
      _s[0] = splitmix64(&seed);
      _s[1] = splitmix64(&seed);
      _s[2] = splitmix64(&seed);
      _s[3] = splitmix64(&seed);
   }
   void xoshiro256::seed(uint64_t seed)
   {
      _s[0] = splitmix64(&seed);
      _s[1] = splitmix64(&seed);
      _s[2] = splitmix64(&seed);
      _s[3] = splitmix64(&seed);
   }
   xoshiro256::result_type xoshiro256::operator()()  {
      const uint64_t result = rotl(_s[1] * 5, 7) * 9;

      const uint64_t t = _s[1] << 17;

      _s[2] ^= _s[0];
      _s[3] ^= _s[1];
      _s[1] ^= _s[2];
      _s[0] ^= _s[3];

      _s[2] ^= t;

      _s[3] = rotl(_s[3], 45);

      return result;
   }
   void xoshiro256::jump(void) {
      static const uint64_t JUMP[] = { 0x180ec6d33cfd0aba, 0xd5a61266f0c9392c, 0xa9582618e03fc9aa, 0x39abdc4529b1661c };

      uint64_t s0 = 0;
      uint64_t s1 = 0;
      uint64_t s2 = 0;
      uint64_t s3 = 0;
      for(int i = 0; i < 4; i++)
         for(int b = 0; b < 64; b++) {
            if (JUMP[i] & UINT64_C(1) << b) {
               s0 ^= _s[0];
               s1 ^= _s[1];
               s2 ^= _s[2];
               s3 ^= _s[3];
            }
            (*this)();
         }
         
      _s[0] = s0;
      _s[1] = s1;
      _s[2] = s2;
      _s[3] = s3;
   }
   void xoshiro256::long_jump()
   {
      static const uint64_t LONG_JUMP[] = { 0x76e15d3efefdcbbf, 0xc5004e441c522fb3, 0x77710069854ee241, 0x39109bb02acbe635 };

      uint64_t s0 = 0;
      uint64_t s1 = 0;
      uint64_t s2 = 0;
      uint64_t s3 = 0;
      for(int i = 0; i < 4; i++)
         for(int b = 0; b < 64; b++) {
            if (LONG_JUMP[i] & UINT64_C(1) << b) {
               s0 ^= _s[0];
               s1 ^= _s[1];
               s2 ^= _s[2];
               s3 ^= _s[3];
            }
            (*this)();
         }
         
      _s[0] = s0;
      _s[1] = s1;
      _s[2] = s2;
      _s[3] = s3;
   }
} // namespace crand


