#include <x86intrin.h>
#include <openssl/bn.h>
#include <util/bn_avx2/get_bn_avx2.h>
#include <util/bn_avx2/show_bn_avx2.h>

//将avx2形式的大数转成普通形式的大数
void bn_avx2to_normal(__m256i A_B[5], BN_ULONG A[5], BN_ULONG B[5]);

//小端存储，limb为64-bit的大数形式转成openssl中的BIGNUM*类型
void normal2bignum(BN_ULONG A[], int size, BIGNUM *bn_A);

// avx2形式转成openssl中的BIGNUM*类型
void avx2to_bignum(__m256i A_B[5], BIGNUM *bn_A, BIGNUM *bn_B);