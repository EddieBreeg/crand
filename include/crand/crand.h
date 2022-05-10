#pragma once

#include "./ctr.h"
#include "./sys_rng.h"
#include "./xorshift.h"
#include "./xoshiro.h"
#include "./lfsr.h"
#include "./splitmix64.h"

#include "./version.h"

#if defined(__cplusplus)

namespace crand{
    using default_engine = xoshiro256;
}

#endif // __cplusplus
