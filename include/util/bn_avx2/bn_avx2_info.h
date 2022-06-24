#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <x86intrin.h>
#include <stdint.h>

/**
 * @brief 得到A_B的20个limb的bit长
 *
 * @param A_B 输入
 * @param size 输出
 * @require
 */
void limb_size(__m256i A_B[5], int size[20]);