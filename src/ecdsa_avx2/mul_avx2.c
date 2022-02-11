/**
 * @file a.c
 *
 * @brief 参考文献 PIOS2020 见ref文件夹
 * 函数 test1 computer_256
 *
 * @version 0.1
 * @date 2022-01-04
 * @author pony (mspony@163.com)
 * @require AVX2基础 见note.md
 */

#include <immintrin.h>

__m256i A_B[5];
__m256i C_D[5];

/**
 * @brief PIOS2020中Algorithm5的实现
 *
 * @param A_B
 * @param C_D
 * @return __m256i*
 * @require 相关数据结构与算法见note.md
 */
int computer_256(__m256i Z[10], __m256i A_B[5], __m256i C_D[5])
{
	__m256i C_D1[5];
	__m256i U[5], V[5];
	__m256i temp, temp1, temp2;
	__m256i zero = _mm256_set_epi64x(0, 0, 0, 0);

	for (int i = 0; i < 5; i++)
	{
		if (i < 4)
		{
			C_D1[i] = _mm256_alignr_epi8(C_D[i + 1], C_D[i], 8);
		}
		else
		{
			C_D1[i] = _mm256_alignr_epi8(C_D[0], C_D[4], 8);
		}
	}

	for (int i = 0; i < 5; i++)
	{
		U[i] = _mm256_shuffle_epi32(A_B[i], 0x44);

		for (int j = 0; j < 5; j++)
		{
			temp = _mm256_mul_epu32(U[i], C_D[j]);
			Z[i + j] = _mm256_add_epi64(Z[i + j], temp);
		}

		V[i] = _mm256_shuffle_epi32(A_B[i], 0xEE);
		for (int j = 0; j < 4; j++)
		{
			temp = _mm256_mul_epu32(V[i], C_D1[j]);
			Z[i + j + 1] = _mm256_add_epi64(Z[i + j + 1], temp);
		}
		// W = MUL(V,<C,D>4)
		temp = _mm256_mul_epu32(V[i], C_D1[4]);
		temp1 = _mm256_blend_epi32(temp, zero, 0x33);
		temp2 = _mm256_blend_epi32(temp, zero, 0xcc);
		Z[i] = _mm256_add_epi64(Z[i], temp1);
		Z[i + 5] = _mm256_add_epi64(Z[i + 5], temp2);
	}

	return 1;
}

/**
 * @brief PIOS2020中Algorithm5,6,7,8的实现
 *
 * @param E_F 其中：E=A*C mod p，F=B*D mod p
 * @param A_B
 * @param C_D
 * @return int，无意义，一直都为1
 * @require 相关数据结构与算法见note.md
 */
int mul_avx2(__m256i E_F[5], __m256i A_B[5], __m256i C_D[5])
{

	// C′D′
	__m256i C_D1[5];
	__m256i Z[10];
	__m256i U[5], V[5];
	__m256i temp, temp1, temp2;
	__m256i zero = _mm256_set_epi64x(0, 0, 0, 0);

	for (int i = 0; i < 5; i++)
	{
		if (i < 4)
		{
			C_D1[i] = _mm256_alignr_epi8(C_D[i + 1], C_D[i], 8);
		}
		else
		{
			// i=5的情况
			C_D1[i] = _mm256_alignr_epi8(C_D[0], C_D[4], 8);
		}
	}

	for (int i = 0; i < 5; i++)
	{
		U[i] = _mm256_shuffle_epi32(A_B[i], 0x44);

		for (int j = 0; j < 5; j++)
		{
			temp = _mm256_mul_epu32(U[i], C_D[j]);
			Z[i + j] = _mm256_add_epi64(Z[i + j], temp);
		}

		V[i] = _mm256_shuffle_epi32(A_B[i], 0xEE);
		for (int j = 0; j < 4; j++)
		{
			temp = _mm256_mul_epu32(V[i], C_D1[j]);
			Z[i + j + 1] = _mm256_add_epi64(Z[i + j + 1], temp);
		}
		// W = MUL(V,<C,D>_{4})
		temp = _mm256_mul_epu32(V[i], C_D1[4]);
		temp1 = _mm256_blend_epi32(temp, zero, 0x33);
		temp2 = _mm256_blend_epi32(temp, zero, 0xcc);
		Z[i] = _mm256_add_epi64(Z[i], temp1);
		Z[i + 5] = _mm256_add_epi64(Z[i + 5], temp2);
	}

	// Algorithm6(line 1- line 13)
	__m256i L[10], M[10], H[10], M_1[10];					  // M_1 为 M pie
	__m256i temp3 = {67108863, 67108863, 67108863, 67108863}; // 2^n-1
	__m256i temp4 = {52, 52, 52, 52};						  // 2n
	__m256i temp5 = {26, 26, 26, 26};						  // n

	for (int i = 4; i < 9; i++)
	{
		L[i] = _mm256_and_si256(Z[i], temp3);
		M[i] = _mm256_srli_epi64(Z[i], 26);
		M[i] = _mm256_and_si256(M[i], temp3);
		H[i] = _mm256_srli_epi64(Z[i], 52);
	}

	L[9] = _mm256_and_si256(Z[9], temp3);
	M[9] = _mm256_srli_epi64(Z[9], 26);

	for (int i = 5; i < 10; i++)
	{
		M_1[i] = _mm256_alignr_epi8(M[i], M[i - 1], 8);
		Z[i] = _mm256_add_epi64(_mm256_add_epi64(L[i], M_1[i]), H[i - 1]);
	}

	Z[9] = _mm256_alignr_epi8(Z[9], M[9], 8);

	// Algorithm8 正式开始约减
	__m256i temp6 = {1, 15, 1, 15}; // SHLV
	__m256i temp7 = {22, 4, 22, 4}; // SHLV
	__m256i temp8 = {-1, 0, -1, 0}; //[111..1,0,11..1,0]

	__m256i fuzhu1 = {10, 0, 10, 0};
	__m256i fuzhu2 = {24, 1, 24, 1};
	__m256i fuzhu3 = {2, 23, 2, 23};

	__m256i Z_1[10]; // Z pie

	E_F[0] = _mm256_add_epi64(Z[0], _mm256_slli_epi64(Z[5], 4));
	E_F[0] = _mm256_add_epi64(E_F[0], _mm256_slli_epi64(Z[6], 24)); // 2
	E_F[0] = _mm256_add_epi64(E_F[0], _mm256_slli_epi64(_mm256_blend_epi32(_mm256_shuffle_epi32(Z[6], 0xb1), _mm256_shuffle_epi32(Z[7], 0xb1), 0xcc), 18));
	E_F[0] = _mm256_add_epi64(E_F[0], _mm256_slli_epi64(Z[7], 12));
	E_F[0] = _mm256_add_epi64(E_F[0], _mm256_slli_epi64(_mm256_blend_epi32(_mm256_shuffle_epi32(Z[7], 0xb1), _mm256_shuffle_epi32(Z_1[8], 0xb1), 0xcc), 6));
	E_F[0] = _mm256_add_epi64(E_F[0], _mm256_slli_epi64(Z[9], 21));
	E_F[0] = _mm256_add_epi64(E_F[0], _mm256_sllv_epi64(_mm256_blend_epi32(_mm256_permute4x64_epi64(Z[9], 0xb1), Z[8], 0xcc), temp6));
	Z_1[8] = _mm256_sub_epi64(zero, Z[8]);
	Z_1[9] = _mm256_sub_epi64(zero, Z[9]);

	E_F[1] = _mm256_sub_epi64(Z[1], _mm256_slli_epi64(Z[5], 16));
	E_F[1] = _mm256_add_epi64(E_F[1], _mm256_sllv_epi64(_mm256_blend_epi32(_mm256_permute4x64_epi64(Z[5], 0xb1), Z[6], 0xcc), temp7)); // 10
	E_F[1] = _mm256_sub_epi64(E_F[1], _mm256_sllv_epi64(_mm256_and_si256(_mm256_shuffle_epi32(Z[6], 0xb1), temp8), fuzhu1));		   // 11
	E_F[1] = _mm256_add_epi64(E_F[1], _mm256_slli_epi64(_mm256_blend_epi32(Z[8], Z_1[8], 0xcc), 12));
	// SHUF(a,b,0x5) => blend(shuf(a,0xb1),shuf(b,0xb1),0xcc)
	E_F[1] = _mm256_add_epi64(E_F[1], _mm256_slli_epi64(_mm256_blend_epi32(_mm256_shuffle_epi32(Z[8], 0xb1), _mm256_shuffle_epi32(Z_1[9], 0xb1), 0xcc), 6));
	E_F[1] = _mm256_add_epi64(E_F[1], _mm256_sllv_epi64(_mm256_blend_epi32(Z[9], Z[7], 0xcc), fuzhu2)); // 14

	E_F[2] = _mm256_add_epi64(Z[2], _mm256_slli_epi64(_mm256_blend_epi32(_mm256_shuffle_epi32(Z[5], 0xb1), _mm256_shuffle_epi32(Z[6], 0xb1), 0xcc), 22));
	E_F[2] = _mm256_add_epi64(E_F[2], _mm256_slli_epi64(Z[7], 4));
	E_F[2] = _mm256_add_epi64(E_F[2], _mm256_slli_epi64(Z[8], 24));
	E_F[2] = _mm256_add_epi64(E_F[2], _mm256_slli_epi64(_mm256_blend_epi32(_mm256_shuffle_epi32(Z[8], 0xb1), _mm256_shuffle_epi32(Z[9], 0xb1), 0xcc), 19));
	E_F[2] = _mm256_add_epi64(E_F[2], _mm256_slli_epi64(Z[9], 12));
	E_F[2] = _mm256_add_epi64(E_F[2], _mm256_slli_epi64(_mm256_and_si256(_mm256_shuffle_epi32(Z[9], 0xb1), temp8), 6));

	E_F[3] = _mm256_add_epi64(Z[3], _mm256_slli_epi64(_mm256_blend_epi32(_mm256_shuffle_epi32(Z[6], 0xb1), _mm256_shuffle_epi32(Z[7], 0xb1), 0xcc), 22));
	E_F[3] = _mm256_add_epi64(E_F[3], _mm256_slli_epi64(Z[8], 4));
	E_F[3] = _mm256_add_epi64(E_F[3], _mm256_slli_epi64(Z[9], 24));
	E_F[3] = _mm256_add_epi64(E_F[3], _mm256_slli_epi64(_mm256_and_si256(_mm256_shuffle_epi32(Z[9], 0xb1), temp8), 19));

	E_F[4] = _mm256_add_epi64(Z[4], _mm256_slli_epi64(Z[5], 20));
	E_F[4] = _mm256_add_epi64(E_F[4], _mm256_sllv_epi64(_mm256_blend_epi32(_mm256_shuffle_epi32(Z[7], 0xb1), _mm256_shuffle_epi32(Z[7], 0xb1), 0xcc), fuzhu3));
	E_F[4] = _mm256_add_epi64(E_F[4], _mm256_slli_epi64(Z[9], 4));

	__m256i T;
	__m256i fuzhu4 = {8, 14, 8, 14};
	__m256i fuzhu5 = {17, 23, 17, 23};
	__m256i fuzhu6 = {5, 11, 5, 11};
	__m256i fuzhu7 = {0, 4, 0, 4};
	__m256i fuzhu8 = {20, 16, 20, 16};
	__m256i fuzhu9 = {0, 20, 0, 20};

	T = _mm256_add_epi64(_mm256_sllv_epi64(Z[6], fuzhu4), _mm256_sllv_epi64(Z[8], fuzhu5));
	T = _mm256_add_epi64(T, _mm256_sllv_epi64(Z[9], fuzhu6));

	E_F[4] = _mm256_add_epi64(E_F[4], _mm256_add_epi64(_mm256_and_si256(_mm256_shuffle_epi32(T, 0xb1), temp8), _mm256_blend_epi32(zero, T, 0xcc)));

	// Algorithm7
	__m256i fuzhu71 = {26, 52, 26, 52};
	__m256i fuzhu81 = {67108863, 4503599627370495, 67108863, 4503599627370495};
	__m256i Q, Q_1;
	H[4] = _mm256_srlv_epi64(E_F[4], fuzhu71);
	E_F[4] = _mm256_and_si256(E_F[4], fuzhu81);
	Q = _mm256_add_epi64(H[4], _mm256_shuffle_epi32(H[4], 0x4e));
	// shuf(a,a,im8) =>_mm256_shuffle_epi32(a,im8)
	Q_1 = _mm256_sub_epi64(zero, Q);
	E_F[0] = _mm256_add_epi64(E_F[0], _mm256_srlv_epi64(_mm256_blend_epi32(Q, zero, 0xcc), fuzhu71));
	E_F[1] = _mm256_add_epi64(E_F[1], _mm256_srlv_epi64(_mm256_blend_epi32(Q, Q_1, 0x33), fuzhu81));
	E_F[4] = _mm256_add_epi64(E_F[4], _mm256_srlv_epi64(_mm256_blend_epi32(Q, zero, 0xcc), fuzhu9));

	for (int i = 0; i < 5; i++)
	{
		L[i] = _mm256_and_si256(E_F[i], temp3);
		M[i] = _mm256_srlv_epi64(E_F[i], temp5);
		M[i] = _mm256_and_si256(M[i], temp3);
		H[i] = _mm256_srlv_epi64(E_F[i], temp4);
	}

	for (int i = 0; i < 5; i++)
	{
		// align(a,b) => _mm256_alignr_epi8(a,b,8)
		if (i > 0)
		{
			M_1[i] = _mm256_alignr_epi8(M[i], M[i - 1], 8);
			E_F[i] = _mm256_add_epi64(_mm256_add_epi64(L[i], M_1[i]), H[i - 1]);
		}
		else
		{
			M_1[i] = _mm256_alignr_epi8(M[0], M[4], 8);
			E_F[i] = _mm256_add_epi64(_mm256_add_epi64(L[0], M_1[0]), H[4]);
		}
	}

	//将E_F[4]赋值给全局变量Z
	for (int i = 0; i < 5; i++)
	{
		Z[i] = E_F[i];
	}

	return 1;
}