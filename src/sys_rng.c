#include "sys_rng.h"

#if (defined(_WIN32) || defined(_WIN64)) && !defined(__WINDOWS__)
#   define __WINDOWS__ 1
#endif

#if defined(__linux__)
    #include <sys/types.h>
    #include <sys/random.h>
#elif defined(unix) || defined(__unix) || defined(__unix__)
    #include <stdio.h>
#elif defined(__WINDOWS__)
    #include <windows.h>
    #include <bcrypt.h>
#endif


int randomize(void *out, unsigned long n){
    #ifdef __linux__

    long ret;
    do
    {
        if((ret = getrandom(out, n, 0)) == -1) return -1;
        n -= ret;
    } while (n);
    #elif defined(unix) || defined(__unix) || defined(__unix__) // other unix based systems
    FILE* dev = fopen("/dev/urandom", "rb");
    if(fread(out, 1, n, dev) < n) return -1;
    fclose(dev);
    #elif defined(__WINDOWS__)

    BCRYPT_ALG_HANDLE handle;
    if(BCryptOpenAlgorithmProvider(&handle, BCRYPT_RNG_ALGORITHM, NULL, 0) < 0) return -1;
    if(BCryptGenRandom(handle, out, n, 0) < 0) return -1;
    BCryptCloseAlgorithmProvider(handle, 0);

    #else
    #error unsupported
    #endif
    // return 0 on success
    return 0;
}