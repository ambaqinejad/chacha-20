//
// Created by Chromium on 02/07/2022.
//

#include "ChaCha20.h"

ChaCha20::ChaCha20(const uint8_t *key, const uint8_t *nonce, uint64_t counter) :
                   block{key, nonce}, position{64} {
    block.setCounter(counter);
}

void ChaCha20::crypt(uint8_t *bytes, size_t n_bytes) {
    for(size_t i = 0; i < n_bytes; i++) {
        if (position >= 64) {
            block.next(keyStream8);
            position = 0;
        }
        bytes[i] ^= keyStream8[position];
        position ++;
    }
}