cmake_minimum_required(VERSION 3.20)
project(TestProject)
set(CMAKE_VERBOSE_MAKEFILE ON)

# SET(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_BUILD_TYPE "Debug")

add_executable(test1 test1.c)
target_link_directories(test1 PRIVATE ~/github/crypto/openssl)
target_link_libraries(test1 libcrypto.a pthread dl)
target_include_directories(test1 PRIVATE ~/github/crypto/openssl/include)