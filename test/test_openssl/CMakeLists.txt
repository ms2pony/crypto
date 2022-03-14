cmake_minimum_required(VERSION 3.20)
project(TestProject)
set(CMAKE_VERBOSE_MAKEFILE ON)

# SET(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_BUILD_TYPE "Debug")

add_executable(test1 test1.c)
target_link_directories(test1 PRIVATE /home/tam/crypto/openssl /home/tam/crypto/util/openssl/build)
target_link_libraries(test1 libcrypto.a pthread dl openssl_util)
target_include_directories(test1 PRIVATE /home/tam/crypto/openssl/include)
target_include_directories(test1 PRIVATE /home/tam/crypto/util/openssl)