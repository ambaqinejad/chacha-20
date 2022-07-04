//
// Created by Chromium on 03/07/2022.
//

#include "ChaCha20Block.h"

ChaCha20Block::ChaCha20Block(const uint8_t *key, const uint8_t *nonce) {
    const uint8_t *constant = (uint8_t *) "expand 32-byte k";
    state_[0] = pack4(constant + 0 * 4);
    state_[1] = pack4(constant + 1 * 4);
    state_[2] = pack4(constant + 2 * 4);
    state_[3] = pack4(constant + 3 * 4);
    state_[4] = pack4(key + 0 * 4);
    state_[5] = pack4(key + 1 * 4);
    state_[6] = pack4(key + 2 * 4);
    state_[7] = pack4(key + 3 * 4);
    state_[8] = pack4(key + 4 * 4);
    state_[9] = pack4(key + 5 * 4);
    state_[10] = pack4(key + 6 * 4);
    state_[11] = pack4(key + 7 * 4);
    // 64 bit counter initialized to zero by default.
    state_[12] = 0;
    state_[13] = 0;
    state_[14] = pack4(nonce + 0 * 4);
    state_[15] = pack4(nonce + 1 * 4);
}

void ChaCha20Block::setCounter(uint64_t counter) {
    // Want to process many blocks in parallel?
    // No problem! Just set the counter to the block you want to process.
    state_[12] = uint32_t(counter);
    state_[13] = counter >> 32;
}

void ChaCha20Block::next(uint32_t *result) {
#define rotl32(a, b) (((a) << (b)) | ((a) >> (32 - (b))))
#define QUARTERROUND(x, a, b, c, d)\
    x[a] += (x)[b]; (x)[d] = rotl32((x)[d] ^ (x)[a], 16); \
    (x)[c] += (x)[d]; (x)[b] = rotl32((x)[b] ^ (x)[c], 12); \
    (x)[a] += (x)[b]; (x)[d] = rotl32((x)[d] ^ (x)[a], 8); \
    (x)[c] += (x)[d]; (x)[b] = rotl32((x)[b] ^ (x)[c], 7);

    // This is where the crazy voodoo magic happens.
    // Mix the bytes a lot and hope that nobody finds out how to undo it.
    for (int i = 0; i < 16; i++) { result[i] = state_[i]; }
    for (int i = 0; i < 10; i++) {
        QUARTERROUND(result, 0, 4, 8, 12)
        QUARTERROUND(result, 1, 5, 9, 13)
        QUARTERROUND(result, 2, 6, 10, 14)
        QUARTERROUND(result, 3, 7, 11, 15)

        QUARTERROUND(result, 0, 5, 10, 15)
        QUARTERROUND(result, 1, 6, 11, 12)
        QUARTERROUND(result, 2, 7, 8, 13)
        QUARTERROUND(result, 3, 4, 9, 14)
    }
    for (int i = 0; i < 16; i++) { result[i] += state_[i]; }
}

void ChaCha20Block::next(uint8_t *keyStream) {
    uint32_t tempKeyStream[16];
    next(tempKeyStream);
    for (size_t i = 0; i < 16; i++) {
        unpack4(tempKeyStream[i], keyStream + i * 4);
    }
}

uint32_t ChaCha20Block::pack4(const uint8_t *a) {
    uint32_t a0(a[0] << 0 * 8);
    uint32_t a1(a[1] << 1 * 8);
    uint32_t a2(a[2] << 2 * 8);
    uint32_t a3(a[3] << 3 * 8);
    uint32_t result = a0 | a1 | a2 | a3;
    return result;
}

void ChaCha20Block::unpack4(uint32_t src, uint8_t *destination) {
    destination[0] = (src >> 0 * 8) & 0xff;
    destination[1] = (src >> 1 * 8) & 0xff;
    destination[2] = (src >> 2 * 8) & 0xff;
    destination[3] = (src >> 3 * 8) & 0xff;
}
