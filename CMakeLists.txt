cmake_minimum_required(VERSION 3.20)
project(my_chacha_20)

set(CMAKE_CXX_STANDARD 14)

add_executable(my_chacha_20 main.cpp ChaCha20.cpp ChaCha20.h ChaCha20Block.cpp ChaCha20Block.h)
