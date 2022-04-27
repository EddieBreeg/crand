#include "rand.h"

#if (defined(_WIN32) || defined(_WIN64)) && !defined(__WINDOWS__)
#   define __WINDOWS__ 1
#endif

#if defined(__linux__)
    #include <sys/types.h>
    #include <sys/random.h>
#elif defined(__WINDOWS__)
    #include <windows.h>
    #define NT_SUCCESS(Status)          (((NTSTATUS)(Status)) >= 0)
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
    
    #elif defined(__WINDOWS__)
    BCRYPT_ALG_HANDLE handle;
    if(!NT_SUCCESS(BCryptOpenAlgorithmProvider(&handle, BCRYPT_RNG_ALGORITHM, NULL, 0))) return -1;
    if(
        !NT_SUCCESS(BCryptGenRandom(handle, out, n, 0))
    ) return -1;
    #else
    #error unsupported
    #endif
    // return 0 on success
    return 0;
}