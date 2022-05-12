#include "crand/sys_rng.h"
#include <random>

int randomize(void *out, unsigned long n){
    std::random_device rd;
    unsigned char *r = (unsigned char*)out + n - (n&3);
    for (uint32_t *p=(uint32_t*)out; p < (uint32_t*)r; p++)
        *p = rd();
    uint32_t x = rd();
    switch (n&3)
    {
    case 3: *r++ = (unsigned char)(x>>16);
    case 2: *r++ = (unsigned char)(x>>8);
    case 1: *r++ = (unsigned char)x;
    }
    return 0;
}
    

