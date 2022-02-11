#include <immintrin.h>
#include <stdio.h>

int main()
{
    __m256i zero = _mm256_set_epi64x(3, 2, 1, 0);
    printf("%lld\n", zero[1]);
}