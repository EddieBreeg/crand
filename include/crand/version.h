#pragma once

#if defined(__cplusplus)
extern "C"{
namespace crand{
#endif // __cplusplus

typedef struct { const int major, minor, patch; } crand_version_t;

crand_version_t crand_get_version();

#if defined(__cplusplus)
}}
#endif // __cplusplus

