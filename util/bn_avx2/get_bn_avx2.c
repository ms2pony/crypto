#include <util/bn_avx2/get_bn_avx2.h>

void get_bn_avx2(__m256i A_B[5], unsigned int seed)
{
	srand(seed);

	for (int i = 0; i < 4; i++)
	{
		A_B[i] = _mm256_set_epi64x(
			// 32-bit转成26-bit
			rand() >> 6, rand() >> 6, rand() >> 6, rand() >> 6);
	};

	//_mm256_set_epi64x为大端分配(从最后一个元素开始分配)
	A_B[4] = _mm256_set_epi64x(rand() >> 10, rand() >> 6, rand() >> 10, rand() >> 6);
}