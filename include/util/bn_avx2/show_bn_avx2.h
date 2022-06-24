#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <x86intrin.h>
#include <stdint.h>

/**
 * @brief 分别打印A_B两个大数的各个limb，小端序打印(低位limb到高位)
 * 并且每个limb还标明bit长度
 *
 * @param A_B
 * @param size 存储着20个limb的bit长度
 * @require
 */
void show_bn_avx2(__m256i A_B[5], int size[20]);

/**
 * @brief 打印出的A_B兼容python的字典
 *
 * @param A_B
 * @require
 */
void show_bn_avx2_2(__m256i A_B[5]);

/**
 * @brief 以python列表形式打印A_B的20个limb
 *
 * @param A_B
 * @require
 */
void show_bn_avx2_py(__m256i A_B[5]);

// 将avx2形式的两个大数以字符串形式打印出来
void show_bn_avx2_hex(__m256i A_B[5], char *s1, char *s2);

// 在show_bn_avx2_hex函数的基础上会对两个大数进行取模
void show_bn_avx2_hex2(__m256i A_B[5], char *s1, char *s2);
