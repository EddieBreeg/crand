#ifndef RAND_H
#define RAND_H

// Writes n random bytes in out, using an external non deterministic entropy source
// Returns: 0 on success, 1 on failure
int randomize(void *out, unsigned long n);

#endif