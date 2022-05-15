#include "crand/version.h"

#ifndef CRAND_VERSION
#define CRAND_VERSION

/* version is defined externally at compile time */
#define CRAND_VERSION_MAJOR 0
#define CRAND_VERSION_MINOR 0
#define CRAND_VERSION_PATCH 0

#endif


crand_version_t crand_get_version(){ return 
    (crand_version_t){CRAND_VERSION_MAJOR, CRAND_VERSION_MINOR, CRAND_VERSION_PATCH}; 
}