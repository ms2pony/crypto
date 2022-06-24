#include <chrono>
#include <iostream>

using namespace std;

extern "C"
{
#include <openssl/bn.h>
#include <util/bn_avx2/get_bn_avx2.h>
#include <util/bn_convert/bn_convert.h>
	int mul_avx2(__m256i E_F[5], __m256i A_B[5], __m256i C_D[5]);
/* Montgomery mul: res = a*b*2^-256 mod P */
#define P256_LIMBS (256 / BN_BITS2)
	void ecp_nistz256_mul_mont(BN_ULONG res[P256_LIMBS],
							   const BN_ULONG a[P256_LIMBS],
							   const BN_ULONG b[P256_LIMBS]);
}

void bench_mul_mod()
{
	double sum = 0;

	__m256i A_B[5];
	__m256i C_D[5];
	__m256i E_F[5];

	BN_ULONG A[5] = {0};
	BN_ULONG B[5] = {0};
	BN_ULONG C[5] = {0};
	BN_ULONG D[5] = {0};
	BN_ULONG E[5] = {0};
	BN_ULONG F[5] = {0};

	unsigned int seed = (unsigned int)time(NULL);

	// Start measuring time

	int iterations = 10000;
	for (int i = 0; i < iterations; i++)
	{
		get_bn_avx2(A_B, seed++);
		get_bn_avx2(C_D, seed++);
		bn_avx2to_normal(A_B, A, B);
		bn_avx2to_normal(C_D, C, D);

		auto begin = chrono::high_resolution_clock::now();
		for (int i = 0; i < iterations; i++)
		{
#ifdef MULAVX2
			mul_avx2(E_F, A_B, C_D);
#else
			ecp_nistz256_mul_mont(E, A, C);
			ecp_nistz256_mul_mont(E, A, C);
#endif
		}
		// Stop measuring time and calculate the elapsed time
		auto end = chrono::high_resolution_clock::now();
		auto elapsed = chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
		// printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
		sum += elapsed.count() * 1e-9;
	}

	cout << "Time measured: " << sum / (iterations * iterations) << " seconds." << endl;
}

int main()
{

	bench_mul_mod();

	return 0;
}