#include "crand/xorshift.h"
#include "crand/splitmix64.h"

static uint32_t xorshift32_state;
static uint64_t xorshift64_state;

void xorshift32_seed(uint64_t seed)
{
    xorshift32_state = (uint32_t)splitmix64(&seed);
}
void xorshift64_seed(uint64_t seed)
{
    xorshift64_state = splitmix64(&seed);
}

uint32_t xorshift32_next()
{
    xorshift32_state ^= xorshift32_state << 13;
    xorshift32_state ^= xorshift32_state >> 17;
    return xorshift32_state ^= (xorshift32_state << 5);
}
uint64_t xorshift64_next()
{
    xorshift64_state ^= xorshift64_state << 13;
    xorshift64_state ^= xorshift64_state >> 7;
    return xorshift64_state ^= (xorshift64_state << 17);
}

