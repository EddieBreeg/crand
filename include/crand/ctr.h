#pragma once

#include <inttypes.h>

void ctr_aes256_seed(const uint8_t key[32], uint64_t nonce);
void ctr_aes256_next(void *output);
uint64_t ctr_aes256_get_counter();
void ctr_aes256_set_counter(uint64_t c);

#ifdef __cplusplus
#include <crand/aes/aes.h>
namespace crand{
    class ctr_aes256
    {
    private:
        aes256 _aes;
        uint64_t _s[2] = {0};
    public:
        ctr_aes256(const uint8_t key[32], uint64_t nonce);
        void operator()(void *output);
        uint64_t counter() const;
        void counter(uint64_t c);
        uint64_t nonce() const;
        void nonce(uint64_t c);
        static constexpr uint64_t keySize() { return 32; }
        static constexpr uint64_t blockSize() { return 16; }
    };    
}

#endif