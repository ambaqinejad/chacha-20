//
// Created by Chromium on 03/07/2022.
//

#ifndef MY_CHACHA_20_CHACHA20BLOCK_H
#define MY_CHACHA_20_CHACHA20BLOCK_H

#include <cstdint>

class ChaCha20Block {
    // This is basically a random number generator seeded with key and nonce.
    // Generates 64 random bytes every time count is incremented.
private:
    uint32_t state_[16];
public:
    ChaCha20Block(const uint8_t key[32], /* 32 ta 8 bits = 256 bits = 8 ta 32 bits */
                  const uint8_t nonce[8] /* 8 ta 8 bits = 64 bits = 2 ta 32 bits */);
    void setCounter(uint64_t counter);
    static uint32_t pack4(const uint8_t *a);
};


#endif //MY_CHACHA_20_CHACHA20BLOCK_H
