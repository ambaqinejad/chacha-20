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
    state_[12] = uint32_t (counter);
    state_[13] = counter >> 32;
}

uint32_t ChaCha20Block::pack4(const uint8_t *a) {
    uint32_t a0(a[0] << 0 * 8);
    uint32_t a1(a[1] << 1 * 8);
    uint32_t a2(a[2] << 2 * 8);
    uint32_t a3(a[3] << 3 * 8);
    uint32_t result = a0 | a1 | a2 | a3;
    return result;
}
