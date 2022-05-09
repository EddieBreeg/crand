#pragma once

#ifdef __cplusplus
extern "C"{
#endif

#include <inttypes.h>
#define CHACHA20_BLOCKSIZE  64

// opaque struct representing the internal state
// for ChaCha20
typedef struct chacha20_state chacha20_state;

// inits the ChaCha20 state from a key, a nonce and an inital counter
chacha20_state* chacha20_init(const void* key, const void* nonce, uint32_t counter);

// generates the next block in the pseudo-random keystream
// and stores the result in the ouput block
void chacha20_block(chacha20_state *state, void* block);

// utility function to encrypt the input data
// stores the result in the output buffer
void chacha20_encrypt(chacha20_state* state, const void* data, uintmax_t len, void *output);

void chacha20_set_key(chacha20_state* chacha, const void *key);
void chacha20_set_nonce(chacha20_state *chacha, const void* nonce);
void chacha20_set_counter(chacha20_state* state, uint32_t c);
uint32_t chacha20_get_counter(chacha20_state* state);

// resource cleaning
void chacha20_clean(chacha20_state* state);

#ifdef __cplusplus
}

namespace crand
{
    class chacha20
    {
    private:
        uint32_t _state[CHACHA20_BLOCKSIZE] = {0};
    public:
        // default constructor -> should only be used when using chacha20 as a CPRNG
        chacha20();
        // constructs the ChaCha20 state from a key, a nonce and an inital counter
        chacha20(void *key, void *nonce, uint32_t counter = 0);
        chacha20(const chacha20&) = delete;
        void set_nonce(void *nonce);
        void set_key(const void *k);
        // utility method to encrypt the input data
        // stores the result in the output buffer
        void encrypt(const void* data, uintmax_t len, void* out);
        // generates the next block in the pseudo-random keystream
        // and stores the result in the ouput block
        void operator()(void *block);
        // generates a block at the given position in the keystream
        void operator()(void *block, uint32_t counter);
        // getter/setter for the internal counter
        uint32_t counter() const;
        void counter(uint32_t c);
        static inline constexpr unsigned blockSize() { return CHACHA20_BLOCKSIZE; };
    };
}


#endif