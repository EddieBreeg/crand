#pragma once

#ifdef __cplusplus
extern "C"{
#endif


#include <inttypes.h>

// Sets the key for the CPRNG. nonce may be 0
void ctr_aes256_seed(const uint8_t key[32], uint64_t nonce);
// Generates the next 128-bit block in the pseudo-random stream
void ctr_aes256_next(void *output);
// Gets the current position in the stream
uint64_t ctr_aes256_get_counter();
// Sets the current position in the stream
void ctr_aes256_set_counter(uint64_t c);

#ifdef __cplusplus
}
#include <crand/aes/aes.h>
namespace crand{
    // Class for the AES256 Counter mode
    class ctr_aes256
    {
    private:
        // AES key schedule
        aes256 _aes;
        // { Counter, nonce}
        uint64_t _s[2] = {0};
    public:
        ctr_aes256(const uint8_t key[32], uint64_t nonce = 0);
        // Generates the next block in the stream, puts the data in `output`
        void operator()(void *output);
        /* Accessor method for the internal counter */
        uint64_t counter() const;
        /* Accessor method for the internal counter */
        void counter(uint64_t c);
        /* Accessor method for the internal nonce */
        uint64_t nonce() const;
        /* Accessor method for the internal nonce */
        void nonce(uint64_t c);
        static constexpr uint64_t keySize() { return 32; }
        static constexpr uint64_t blockSize() { return 16; }
    };    
}

#endif