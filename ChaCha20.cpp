//
// Created by Chromium on 02/07/2022.
//

#include "ChaCha20.h"

ChaCha20::ChaCha20(const uint8_t *key, const uint8_t *nonce, uint64_t counter) :
                   block{key, nonce}, position{64} {
    block.setCounter(counter);
}

uint8_t* ChaCha20::crypt(uint8_t *bytes, size_t n_bytes) {
    block.next(keyStream8);
    for(size_t i = 0; i < n_bytes; i++) {
        if (position >= 64) {
            position = 0;
        }
        bytes[i] ^= keyStream8[position];
        position ++;
    }
    return keyStream8;
}

void ChaCha20::decrypt(uint8_t *bytes, size_t n_bytes, int threshhold) {
    for(size_t i = 0; i < n_bytes; i++) {
        if (threshhold >= 64) {
            threshhold = 0;
        }
        bytes[i] ^= keyStream8[threshhold];
        threshhold ++;
    }
}