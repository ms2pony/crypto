#define BN_ULONG unsigned long
#define P256_LIMBS (256 / BN_BITS2)
#define BN_BITS2 64

#include <stdio.h>
#include <immintrin.h>
#include <x86intrin.h>
#include <stdint.h>

__m256i A_B[5];
__m256i C_D[5];
__m256i Z[10];

__m256i *test1();

void ecp_nistz256_mul_mont(BN_ULONG res[P256_LIMBS],
						   const BN_ULONG a[P256_LIMBS],
						   const BN_ULONG b[P256_LIMBS]);

uint64_t rdtsc()
{
	uint64_t a, d;
	asm volatile("mfence");
	asm volatile("rdtsc"
				 : "=a"(a), "=d"(d));
	a = (d << 32) | a;
	asm volatile("mfence");
	return a;
};

__m256i *computer_256(__m256i A_B[5], __m256i C_D[5]);

int main()
{
	const BN_ULONG a[4] = {1};
	const BN_ULONG b[4] = {1};
	BN_ULONG res[4] = {0, 0, 0, 0};

	// ecp_nistz256_mul_mont(res,a,b);

	// for(int i=0;i<4;i++){
	// 	printf("%lu\n",res[i]);
	// }
	// 	printf("\n");

	A_B[0] = _mm256_set_epi64x(51423524, 56030310, 11397043, 15645338);
	A_B[1] = _mm256_set_epi64x(25976630, 62398102, 48583030, 45096011);
	A_B[2] = _mm256_set_epi64x(29954667, 51347875, 19015266, 26780030);
	A_B[3] = _mm256_set_epi64x(39376672, 54947324, 27671603, 5688755);
	A_B[4] = _mm256_set_epi64x(16914210, 2041311, 12582839, 214373);
	C_D[0] = _mm256_set_epi64x(24198817, 61994887, 26788201, 35879724);
	C_D[1] = _mm256_set_epi64x(10215065, 930661, 24411185, 48789969);
	C_D[2] = _mm256_set_epi64x(12818618, 17935313, 16939434, 20757944);
	C_D[3] = _mm256_set_epi64x(28815027, 8017293, 43993867, 64360620);
	C_D[4] = _mm256_set_epi64x(45174287, 911207, 27684150, 3961645);

	unsigned long x1, x2, myt1, myt2;

	// x1=rdtsc();
	// for(int i=0;i<100000000;i++){
	// 	test1();
	// }
	// x2=rdtsc();
	// myt2=x2-x1;

	x1 = rdtsc();
	for (int i = 0; i < 100000000; i++)
	{
		ecp_nistz256_mul_mont(res, a, b);
	}
	x2 = rdtsc();
	myt1 = x2 - x1;

	// printf("myt1:\n%lu\n",myt1);
	// printf("myt2:\n%lu\n",myt2);
}