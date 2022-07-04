//
// Created by Chromium on 02/07/2022.
//

#ifndef MY_CHACHA_20_CHACHA20_H
#define MY_CHACHA_20_CHACHA20_H
#include <cstdint>
#include "ChaCha20Block.h"

class ChaCha20 {
    // XORs plaintext/encrypted bytes with whatever Chacha20Block generates.
    // Encryption and decryption are the same operation.
    // Chacha20Blocks can be skipped, so this can be done in parallel.
    // If keys are reused, messages can be decrypted.
    // Known encrypted text with known position can be tampered with.
    // See https://en.wikipedia.org/wiki/Stream_cipher_attack
private:
    ChaCha20Block block;
    uint8_t keyStream8[64];
    size_t position;

public:
    ChaCha20(const uint8_t key[32], /* 32 ta 8 bits = 256 bits = 8 ta 32 bits */
             const uint8_t nonce[8], /* 8 ta 8 bits = 64 bits = 2 ta 32 bits */
             uint64_t counter = 0 /* 64 bits = 2 ta 32 bits */);

    void crypt(uint8_t *bytes, size_t n_bytes);
};

#endif //MY_CHACHA_20_CHACHA20_H
