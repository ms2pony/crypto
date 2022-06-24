#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <x86intrin.h>
#include <stdint.h>

void get_bn_avx2(__m256i A_B[5], unsigned int seed);