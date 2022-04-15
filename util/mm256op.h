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
void show_mm256_2bn1(__m256i A_B[5], int size[20]);

void mm256_2bn_limbsize(__m256i A_B[5], int size[20]);

void get_mm256_2bn(__m256i A_B[5],unsigned int seed);

/**
 * @brief 得到A_B的20个limb的bit长
 * 
 * @param A_B 输入
 * @param size 输出
 * @require 
 */
void mm256_2bn_limbsize(__m256i A_B[5], int size[20]);

/**
 * @brief 打印出的A_B兼容python的字典
 *
 * @param A_B
 * @require
 */
void show_mm256_2bn(__m256i A_B[5]);