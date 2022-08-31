#include <stdio.h>
#include "clock.h"
#include <x86intrin.h>
void mont_mul_opt(unsigned long **res);
unsigned long* mul(unsigned long A[10],unsigned long B[10]);
int mul_avx2(__m256i E_F[5], __m256i A_B[5], __m256i C_D[5]);

extern unsigned long A[10],B[10];

int main()
{
    const int BENCH = 1000;
    unsigned long *res;

    __m256i A_B[5];
    __m256i C_D[5];
    __m256i E_F[5] = {0};
    A_B[0] = _mm256_set_epi64x(15645338, 11397043, 56030310, 51423524);
    A_B[1] = _mm256_set_epi64x(45096011, 48583030, 62398102, 25976630);
    A_B[2] = _mm256_set_epi64x(26780030, 19015266, 51347875, 29954667);
    A_B[3] = _mm256_set_epi64x(5688755, 27671603, 54947324, 39376672);
    A_B[4] = _mm256_set_epi64x(214373, 12582839, 2041311, 16914210);

    C_D[0] = _mm256_set_epi64x(35879724, 26788201, 61994887, 24198817);
    C_D[1] = _mm256_set_epi64x(48789969, 24411185, 930661, 10215065);
    C_D[2] = _mm256_set_epi64x(20757944, 16939434, 17935313, 12818618);
    C_D[3] = _mm256_set_epi64x(64360620, 43993867, 8017293, 28815027);
    C_D[4] = _mm256_set_epi64x(3961645, 27684150, 911207, 45174287);

    // CLOCKS(MontMul,mont_mul_opt(&res));
    CLOCKS(MontMul,mul_avx2(E_F, A_B, C_D));


}