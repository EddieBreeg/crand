

#include "crand/chacha20/chacha20_common.h"
#include "crand/chacha20/chacha20.h"
#include <random>


namespace crand
{
    void chacha20::set_key(const void *key){
        for (int i = 0; i < 32; i++)
            ((uint8_t*)_state)[16+i] = ((uint8_t*)key)[i];
    }
    void chacha20::set_nonce(void *nonce){
        for (int i = 0; i < 12; i++)
            ((uint8_t*)_state)[52+i] = ((uint8_t*)nonce)[i];
    }
    chacha20::chacha20(){
        _state[0] = 0x61707865;
        _state[1] = 0x3320646e;
        _state[2] = 0x79622d32;
        _state[3] = 0x6b206574;
        std::random_device rd; // non deterministic random source
        for(int i=4; i<16; ++i) _state[i] = rd();
        _state[12] = 0;
    }
    chacha20::chacha20(void *key, void* nonce, uint32_t counter)
    {
        _state[0] = 0x61707865;
        _state[1] = 0x3320646e;
        _state[2] = 0x79622d32;
        _state[3] = 0x6b206574;
        set_key(key);
        _state[12] = counter;
        set_nonce(nonce);
    }
    uint32_t chacha20::counter() const{
        return _state[12];
    }
    void chacha20::counter(uint32_t c){
        _state[12] = c;
    }

    void chacha20::operator()(void *block){
        uint32_t *w = (uint32_t*)block; // working buffer
        for (int i = 0; i < 16; i++)
            w[i] = _state[i];      
        for (int i = 0; i < 10; i++)
            inner_block(w);
        for (int i = 0; i < 16; i++)
        {
            w[i] += _state[i];  
            lendian32(w[i]);  
        }
        _state[12]++;
    }
    void chacha20::operator()(void* block, uint32_t counter){
        _state[12] = counter;
        this->operator()(block);
    }
    void chacha20::encrypt(const void* data, uintmax_t len, void* out){
        uint8_t stream[chacha20::blockSize()];
        int r = len & 63;
        uintmax_t n = len - r;
        // encrypt whole blocks
        for (uintmax_t i = 0; i < n; i+=chacha20::blockSize())
        {
            this->operator()(stream);
            for (int j = 0; j < chacha20::blockSize(); j++)
                ((uint8_t*)out)[i+j] = ((uint8_t*)data)[i+j] ^ stream[j];        
        }
        // take care of the remaining bytes, if any
        if(r){
            this->operator()(stream);
            for (int i = 0; i < r; i++)
                ((uint8_t*)out)[i+n] = ((uint8_t*)data)[i+n] ^ stream[i];
        }
    }
} // namespace crand


