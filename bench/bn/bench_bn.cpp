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

	__m256i A_B[5];
	__m256i C_D[5];
	__m256i E_F[5];

	BN_ULONG A[5] = {0};
	BN_ULONG B[5] = {0};
	BN_ULONG C[5] = {0};
	BN_ULONG D[5] = {0};
	BN_ULONG E[5] = {0};
	BN_ULONG F[5] = {0};
}

void base1(int iterations)
{
	for (int i = 0; i < iterations; i++)
	{
		mul_avx2(E_F, A_B, C_D);
	}
}

void base2(int iterations)
{
	for (int i = 0; i < iterations; i++)
	{
		ecp_nistz256_mul_mont(E, A, C);
		ecp_nistz256_mul_mont(E, A, C);
	}
}

void bench_mul_mod()
{
	double sum = 0, sum2 = 0;

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
		base1(iterations);
		// Stop measuring time and calculate the elapsed time
		auto end = chrono::high_resolution_clock::now();
		auto elapsed = chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
		// printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
		sum += elapsed.count() * 1e-9;

		begin = chrono::high_resolution_clock::now();
		base2(iterations);
		// Stop measuring time and calculate the elapsed time
		end = chrono::high_resolution_clock::now();
		elapsed = chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
		// printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
		sum2 += elapsed.count() * 1e-9;
	}

	cout << "Time measured(mul_avx2): " << endl
		 << sum / (iterations * iterations) << " seconds.\t"
		 << sum / (iterations * iterations) * 2.6e+9 << " reference cycles." << endl;

	cout << "Time measured(ecp_nistz256_mul_mont): " << endl
		 << sum2 / (iterations * iterations) << " seconds.\t"
		 << sum2 / (iterations * iterations) * 2.6e+9 << " reference cycles." << endl;
}

int main()
{

	bench_mul_mod();

	return 0;
}