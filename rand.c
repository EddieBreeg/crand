#include "rand.h"

#if (defined(_WIN32) || defined(_WIN64)) && !defined(__WINDOWS__)
#   define __WINDOWS__ 1
#endif

#if defined(__linux__)
    #include <sys/types.h>
    #include <sys/random.h>
#endif



long randomize(void *out, unsigned long n){
    #ifdef __linux__
    return getrandom(out, n, 0);
    #else
    #error unsupported
    #endif
}