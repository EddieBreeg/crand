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
// and stores the result in the ouput `block`
void chacha20_block(chacha20_state *state, void* block);

// utility function to encrypt the input `data`
// stores the result in the `output` buffer
void chacha20_encrypt(chacha20_state* state, const void* data, uintmax_t len, void *output);

// sets the key for the cipher
void chacha20_set_key(chacha20_state* chacha, const void *key);
// sets the nonce for the cipher
void chacha20_set_nonce(chacha20_state *chacha, const void* nonce);
// Retrieves the current position in the pseudo-random stream
uint32_t chacha20_get_counter(chacha20_state* state);
// Sets the current position in the pseudo-random stream
void chacha20_set_counter(chacha20_state* state, uint32_t c);

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
        // default constructor: generates a random key/nonce pair
        chacha20();
        // constructs the ChaCha20 state from a key, a nonce and an inital counter
        chacha20(void *key, void *nonce, uint32_t counter = 0);
        chacha20(const chacha20&) = delete;
        /* Sets the key for the cipher */
        void set_key(const void *k);
        /* Sets the nonce for the cipher */
        void set_nonce(void *nonce);
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