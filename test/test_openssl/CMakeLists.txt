cmake_minimum_required(VERSION 3.20)
project(TestProject)
set(CMAKE_VERBOSE_MAKEFILE ON)

# SET(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_BUILD_TYPE "Debug")

add_executable(convert_test convert_test.c)
target_link_directories(convert_test PRIVATE ~/github/crypto/openssl)
target_link_libraries(convert_test libcrypto.a pthread dl)
target_include_directories(convert_test PRIVATE ~/github/crypto/openssl/include)