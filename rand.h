#ifndef RAND_H
#define RAND_H

// writes n random bytes in out, using system's default RNG
// Returns: 0 on success, 1 on failure
int randomize(void *out, unsigned long n);

#endif