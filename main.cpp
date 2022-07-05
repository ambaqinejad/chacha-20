#include <vector>
#include <cassert>
#include <iostream>
#include "ChaCha20.h"

typedef std::vector<uint8_t> Bytes;
uint8_t charToUint[256];

Bytes strToBytes(const char *src) {
    return Bytes (src, src + strlen(src));
}

Bytes hexToRaw(const Bytes &src) {
    size_t n = src.size();
    assert(n%2 == 0);
    Bytes result(n/2);
    for (size_t i = 0; i < n/2; i++) {
        uint8_t index1 = src[i*2 + 0];
        uint8_t index2 = src[i*2 + 1];
        uint8_t hi = charToUint[index1];
        uint8_t lo = charToUint[index2];
        hi <<= 4;
        result[i] = hi | lo;
    }
    return result;
}

void crypt(const char *textKey, //64 characters/512 bit
           const char *textNonce, //16 characters/128 bit
           const char *plainText,
           uint64_t counter //64 bits
           ) {
    Bytes key = hexToRaw(strToBytes(textKey));
    Bytes nonce = hexToRaw(strToBytes(textNonce));
    Bytes plain = strToBytes(plainText);
    ChaCha20 chaCha20(key.data(), nonce.data(), counter);
    Bytes result {plain};
    uint8_t* keyStream8 = chaCha20.crypt(&result[0], result.size());
    std::cout << "plain 1: " << plainText << std::endl;
    std::cout << "plain 2: " << plain.data() << std::endl;
    std::cout << "After encryption: " << result.data() << std::endl;
    ChaCha20 chaCha201(key.data(), nonce.data(), counter);
    chaCha201.crypt(&result[0], result.size());
    std::cout << "After decryption: " << result.data() << std::endl;
    std::cout << strlen(plainText) << std::endl;
    std::cout << plain.size() << std::endl;
    std::cout << result.size() << std::endl;
    std::cout << (result.data() == plain.data()) << std::endl;
    std::string a  = reinterpret_cast<const char *const>(result.);
    std::cout << a;
    assert(result == plain);
    assert(a == plainText);
}

int main() {
    for (size_t i = 0; i < 10; i++) {
        charToUint[i + '0'] = i;
    }
    for (size_t i = 0; i < 26; i++) {
        charToUint[i + 'a'] = i;
    }
    for (size_t i = 0; i < 26; i++) {
        charToUint[i + 'A'] = i;
    }

//    crypt("1c9240a5eb55d38af333888604f6b5f0473917c1402b80099dca5cbc207075c0",
//          "0000000000000002",
//          "2754776173206272696c6c69672c20616e642074686520736c6974687920746f7665730a446964206779726520616e642067696d626c6520696e2074686520776162653a0a416c6c206d696d737920776572652074686520626f726f676f7665732c0a416e6420746865206d6f6d65207261746873206f757467726162652e",
//          42);

    crypt("1c9240a5eb55d38af333888604f6b5f0473917c1402b80099dca5cbc207075c0",
          "0000200100000002",
          "My name is Amir Hosein and I'm testing chacha20 algorithm",
          42);
    return 0;
}
