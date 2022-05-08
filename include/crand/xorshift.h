#pragma once

#include <inttypes.h>

static inline uint32_t xoshift32(uint32_t reg){
    reg ^= reg << 13;
    reg ^= reg >> 17;
    return reg ^ (reg << 5);
}

static inline uint64_t xoshift64(uint64_t reg){
    reg ^= reg << 13;
    reg ^= reg >> 7;
    return reg ^ (reg << 17);
}