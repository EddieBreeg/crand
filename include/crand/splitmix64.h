#pragma once

#include <stdint.h>

/* SplitMix64 generator
Only used to seed other generators */
static inline uint64_t splitmix64(uint64_t* state) {
	uint64_t result = (*state += 0x9E3779B97f4A7C15);
	result = (result ^ (result >> 30)) * 0xBF58476D1CE4E5B9;
	result = (result ^ (result >> 27)) * 0x94D049BB133111EB;
	return result ^ (result >> 31);
}
