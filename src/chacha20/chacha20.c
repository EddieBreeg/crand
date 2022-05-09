#include "crand/chacha20/chacha20.h"
#include "crand/chacha20/chacha20_common.h"
#include <stdlib.h>

typedef struct chacha20_state
{
    uint32_t s[16]; // the state buffer
} chacha20_state;

chacha20_state* chacha20_init(const void* key, const void* nonce, uint32_t counter){
    chacha20_state *state = malloc(sizeof(*state));
    if(!state) return NULL;
    state->s[0] = 0x61707865;
    state->s[1] = 0x3320646e;
    state->s[2] = 0x79622d32;
    state->s[3] = 0x6b206574;
    chacha20_set_key(state, key);
    chacha20_set_nonce(state, nonce);
    state->s[12] = counter;
    return state;
}
void chacha20_set_key(chacha20_state* chacha, const void *key){
    for (int i = 0; i < 32; i++)
        ((uint8_t*)chacha->s)[16+i] = ((uint8_t*)key)[i];
}
void chacha20_set_nonce(chacha20_state *chacha, const void* nonce){
    for (int i = 0; i < 12; i++)
        ((uint8_t*)chacha->s)[52+i] = ((uint8_t*)nonce)[i];
}
void chacha20_block(chacha20_state *s, void* block){
    uint32_t *w = (uint32_t*)block;
    for (size_t i = 0; i < 16; i++)
        w[i] = s->s[i];      
    for (size_t i = 0; i < 10; i++)
        inner_block(w);
    for (size_t i = 0; i < 16; i++)
    {
        w[i] += s->s[i];
        lendian32(w[i]);
    }
    s->s[12]++;
}
void chacha20_encrypt(chacha20_state* s, const void* data, uintmax_t len, void* out){
    uint8_t stream[CHACHA20_BLOCKSIZE];
    int r = len & 63;
    uintmax_t n = len - r;
    for (uintmax_t i = 0; i < n; i+=CHACHA20_BLOCKSIZE)
    {
        chacha20_block(s, stream);
        for (int j = 0; j < CHACHA20_BLOCKSIZE; j++)
            ((uint8_t*)out)[i+j] = ((uint8_t*)data)[i+j] ^ stream[j];        
    }
    if(r){
        chacha20_block(s, stream);
        for (int i = 0; i < r; i++)
            ((uint8_t*)out)[i+n] = ((uint8_t*)data)[i+n] ^ stream[i];
    }
}
void chacha20_set_counter(chacha20_state* state, uint32_t c){
    state->s[12] = c;
}
uint32_t chacha20_get_counter(chacha20_state* state){
    return state->s[12];
}
void chacha20_clean(chacha20_state* s){
    free(s);
}