#pragma once

/* Convenience header, includes all you need to use the library */

#include "./ctr.h"
#include "./sys_rng.h"
#include "./xorshift.h"
#include "./xoshiro.h"
#include "./lfsr.h"
#include "./chacha20/chacha20.h"
#include "./splitmix64.h"

#include "./version.h"

#if defined(__cplusplus)

namespace crand{
    using default_engine = xoshiro256;
}

#endif // __cplusplus
