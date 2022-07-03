//
// Created by Chromium on 02/07/2022.
//

#include "ChaCha20.h"

ChaCha20::ChaCha20(const uint8_t *key, const uint8_t *nonce, uint64_t counter) :
                   block{key, nonce}, position{64} {
    block.setCounter(counter);
}