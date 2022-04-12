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

#include <x86intrin.h>
#include <stdio.h>

/**
 * @brief PIOS2020中Algorithm5,6,7,8的实现
 *
 * @param E_F 其中：E=A*C mod p，F=B*D mod p
 * @param A_B
 * @param C_D
 * @output E_F
 * @return int，无意义，一直都为1
 * @require 相关数据结构与算法见note.md
 */
int mul_avx2(__m256i E_F[5], __m256i A_B[5], __m256i C_D[5])
{

	__m256i C_D1[5]; // [C^{\prime},D^{\prime}]

	__m256i Z[10];
	__m256i U[5], V[5];
	__m256i temp, temp1, temp2;
	__m256i zero = _mm256_set_epi64x(0, 0, 0, 0);

	//对Z初始化，全部赋值为0
	for (int i = 0; i < 10; i++)
	{
		Z[i] = _mm256_set_epi64x(0, 0, 0, 0);
	}

	// get C_D1, C_D1[i]=[ C[2i+1], C[2i+2], D[2i+1], D[2i+2] ]
	// C_D1[4] = [C[9],C[0],D[9],D[0]]
	for (int i = 0; i < 5; i++)
	{
		if (i < 4)
		{
			// C_D1[i]=[ C[2i+1], C[2i+2], D[2i+1], D[2i+2] ]
			C_D1[i] = _mm256_alignr_epi8(C_D[i + 1], C_D[i], 8);
		}
		else
		{
			// i=4的情况
			// [C[9],C[0],D[9],D[0]]
			C_D1[i] = _mm256_alignr_epi8(C_D[0], C_D[4], 8);
		}
	}

	// 计算，得到A*C和B*D
	for (int i = 0; i < 5; i++)
	{
		// 0x44=>01000100b=>01 01(四进制，从低到高)
		// U[i]=[A[2i],A[2i],B[2i],B[2i]]
		U[i] = _mm256_shuffle_epi32(A_B[i], 0x44);
		for (int j = 0; j < 5; j++)
		{
			temp = _mm256_mul_epu32(U[i], C_D[j]); // [ A[2i]*C[2j], A[2i]*C[2j+1], B[2i]*C[2j], B[2i]*C[2j+1] ]
			Z[i + j] = _mm256_add_epi64(Z[i + j], temp);
		}

		// 0xEE=>11101110b=>23 23(四进制，从左到右是对应从低位到高位)
		// V[i]=[A[2i+1],A[2i+1],B[2i+1],B[2i+1]]
		V[i] = _mm256_shuffle_epi32(A_B[i], 0xEE);
		for (int j = 0; j < 4; j++)
		{
			temp = _mm256_mul_epu32(V[i], C_D1[j]); // [ A[2i+1]*C[2j+1], A[2i+1]*C[2j+2], B[2i+1]*D[2j+1], B[2i+1]*D[2j+2] ]
			Z[i + j + 1] = _mm256_add_epi64(Z[i + j + 1], temp);
		}

		// W = MUL(V,<C,D>_{4})
		// C_D1[4] = [ C[9], C[0], D[9], D[0] ], V[i]=[ A[2i+1], A[2i+1], B[2i+1], B[2i+1] ]
		// V[i]*C_D1[4]=[ C[9]*A[2i+1], C[0]*A[2i+1], D[9]*B[2i+1], D[0]*B[2i+1] ]
		temp = _mm256_mul_epu32(V[i], C_D1[4]);

		// 0xcc=>11 00 11 00b=>(从左到右是对应从低位到高位)=> temp1= [ 0, C[0]*A[2i+1], 0, D[0]*B[2i+1] ]
		temp1 = _mm256_blend_epi32(temp, zero, 0x33);
		// 0x33=>00 11 00 11b=> temp2= [ C[9]*A[2i+1], 0, D[9]*B[2i+1], 0 ]
		temp2 = _mm256_blend_epi32(temp, zero, 0xcc);

		Z[i] = _mm256_add_epi64(Z[i], temp1);
		Z[i + 5] = _mm256_add_epi64(Z[i + 5], temp2);
	}

	// Algorithm6(line 1- line 13)
	__m256i L[10], M[10], H[10] = {0}, M_1[10], H_1[10];	  // M_1 为 M^{\prime}
	__m256i temp3 = {67108863, 67108863, 67108863, 67108863}; // 67108863=2^{n^{\prime}}-1,n^{\prime}=26
	__m256i temp4 = {52, 52, 52, 52};						  // 2n^{\prime}=52
	__m256i temp5 = {26, 26, 26, 26};						  // n^{\prime}=26

	// 4503599627370495=2^{n^{\prime}}-1,n^{\prime}=52
	__m256i mask1 = {4503599627370495, 4503599627370495, 4503599627370495, 4503599627370495};

	for (int i = 4; i < 9; i++)
	{
		L[i] = _mm256_and_si256(Z[i], temp3);
		M[i] = _mm256_srli_epi64(Z[i], 26);
		M[i] = _mm256_and_si256(M[i], temp3);
		H[i] = _mm256_srli_epi64(Z[i], 52);
	}

	L[9] = _mm256_and_si256(Z[9], temp3);

	// M[9]= [ M91, M92, ...], 其中M91小于26bit，M92为0
	M[9] = _mm256_srli_epi64(Z[9], 26);

	for (int i = 5; i < 10; i++)
	{
		// M_1[i]=[ M[2i-1], M[2i],... ]
		M_1[i] = _mm256_alignr_epi8(M[i], M[i - 1], 8);
		// H_1[i] = _mm256_alignr_epi8(H[i], H[i - 1], 8);

		// L[i]=[ L[2i], L[2i+1],... ]
		Z[i] = _mm256_add_epi64(_mm256_add_epi64(L[i], M_1[i]), H[i - 1]);
	}

	// 0xcc=>00110011b(从左到右是对应从低位到高位)=>Z[4]=[ Z[4*2], L[4*2+1], ... ]
	Z[4] = _mm256_blend_epi32(_mm256_and_si256(Z[4], mask1), L[4], 0xcc);

	// Algorithm8 正式开始约减
	__m256i temp6 = {15, 1, 15, 1}; // SHLV
	__m256i temp7 = {4, 22, 4, 22}; // SHLV
	__m256i temp8 = {0, -1, 0, -1}; //[111..1,0,11..1,0]

	__m256i fuzhu1 = {0, 10, 0, 10};
	__m256i fuzhu2 = {1, 24, 1, 24};
	__m256i fuzhu3 = {23, 2, 23, 2};

	__m256i Z_1[10]; // Z pie

	E_F[0] = _mm256_add_epi64(Z[0], _mm256_slli_epi64(Z[5], 4));
	E_F[0] = _mm256_add_epi64(E_F[0], _mm256_slli_epi64(Z[6], 24));

	// 0x4e=>2 3 0 1, (四进制数：从左到右是对应从低位到高位)
	// 0xcc=> 00110011 (从低位到高位)
	//_mm256_blend_epi32(_mm256_shuffle_epi32(Z[6], 0xb1)=[]
	E_F[0] = _mm256_add_epi64(E_F[0], _mm256_slli_epi64(_mm256_blend_epi32(_mm256_shuffle_epi32(Z[6], 0x4e), _mm256_shuffle_epi32(Z[7], 0x4e), 0xcc), 18));

	E_F[0] = _mm256_add_epi64(E_F[0], _mm256_slli_epi64(Z[7], 12));
	E_F[0] = _mm256_add_epi64(E_F[0], _mm256_slli_epi64(_mm256_blend_epi32(_mm256_shuffle_epi32(Z[7], 0x4e), _mm256_shuffle_epi32(Z[8], 0x4e), 0xcc), 6));
	E_F[0] = _mm256_add_epi64(E_F[0], _mm256_slli_epi64(Z[9], 21));

	// 0xb1=>1 0 3 2 (从低位到高位)
	E_F[0] = _mm256_add_epi64(E_F[0], _mm256_sllv_epi64(_mm256_blend_epi32(_mm256_permute4x64_epi64(Z[9], 0xb1), Z[8], 0xcc), temp6));

	// E_F[1]
	Z_1[8] = _mm256_sub_epi64(zero, Z[8]);
	Z_1[9] = _mm256_sub_epi64(zero, Z[9]);
	E_F[1] = _mm256_sub_epi64(Z[1], _mm256_slli_epi64(Z[5], 16));

	// 0xcc=> 00110011 (从低位到高位), 0xb1=>1 0 3 2 (从低位到高位)
	E_F[1] = _mm256_add_epi64(E_F[1], _mm256_sllv_epi64(_mm256_blend_epi32(Z[6], _mm256_permute4x64_epi64(Z[5], 0xb1), 0xcc), temp7));
	E_F[1] = _mm256_sub_epi64(E_F[1], _mm256_sllv_epi64(_mm256_and_si256(_mm256_shuffle_epi32(Z[6], 0x4e), temp8), fuzhu1));
	E_F[1] = _mm256_add_epi64(E_F[1], _mm256_slli_epi64(_mm256_blend_epi32(Z[8], Z_1[8], 0xcc), 12));
	// SHUF(a,b,0x5) => blend(shuf(a,0xb1),shuf(b,0xb1),0xcc)
	E_F[1] = _mm256_add_epi64(E_F[1], _mm256_slli_epi64(_mm256_blend_epi32(_mm256_shuffle_epi32(Z[8], 0x4e), _mm256_shuffle_epi32(Z_1[9], 0x4e), 0xcc), 6));
	E_F[1] = _mm256_add_epi64(E_F[1], _mm256_sllv_epi64(_mm256_blend_epi32(Z[9], Z[7], 0xcc), fuzhu2)); // 14

	E_F[2] = _mm256_add_epi64(Z[2], _mm256_slli_epi64(_mm256_blend_epi32(_mm256_shuffle_epi32(Z[5], 0x4e), _mm256_shuffle_epi32(Z[6], 0x4e), 0xcc), 22));
	E_F[2] = _mm256_add_epi64(E_F[2], _mm256_slli_epi64(Z[7], 4));
	E_F[2] = _mm256_add_epi64(E_F[2], _mm256_slli_epi64(Z[8], 24));
	E_F[2] = _mm256_add_epi64(E_F[2], _mm256_slli_epi64(_mm256_blend_epi32(_mm256_shuffle_epi32(Z[8], 0x4e), _mm256_shuffle_epi32(Z[9], 0x4e), 0xcc), 19));
	E_F[2] = _mm256_add_epi64(E_F[2], _mm256_slli_epi64(Z[9], 12));
	E_F[2] = _mm256_add_epi64(E_F[2], _mm256_slli_epi64(_mm256_blend_epi32(_mm256_shuffle_epi32(Z[9], 0x4e), zero, 0xcc), 6));

	E_F[3] = _mm256_add_epi64(Z[3], _mm256_slli_epi64(_mm256_blend_epi32(_mm256_shuffle_epi32(Z[6], 0x4e), _mm256_shuffle_epi32(Z[7], 0x4e), 0xcc), 22));
	E_F[3] = _mm256_add_epi64(E_F[3], _mm256_slli_epi64(Z[8], 4));
	E_F[3] = _mm256_add_epi64(E_F[3], _mm256_slli_epi64(Z[9], 24));
	E_F[3] = _mm256_add_epi64(E_F[3], _mm256_slli_epi64(_mm256_blend_epi32(_mm256_shuffle_epi32(Z[9], 0x4e), zero, 0xcc), 19));

	// 0xcc=> 00110011 (从低位到高位)
	E_F[4] = _mm256_add_epi64(Z[4], _mm256_slli_epi64(Z[5], 20));
	E_F[4] = _mm256_add_epi64(E_F[4], _mm256_sllv_epi64(_mm256_permute4x64_epi64(Z[7], 0xb1), fuzhu3));

	E_F[4] = _mm256_add_epi64(E_F[4], _mm256_slli_epi64(Z[9], 4));

	// printf("E=[%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld]\n", E_F[0][0], E_F[0][1], E_F[1][0], E_F[1][1], E_F[2][0], E_F[2][1], E_F[3][0], E_F[3][1], E_F[4][0], E_F[4][1]);
	// printf("F=[%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld]\n", E_F[0][2], E_F[0][3], E_F[1][2], E_F[1][3], E_F[2][2], E_F[2][3], E_F[3][2], E_F[3][3], E_F[4][2], E_F[4][3]);

	__m256i T;
	__m256i fuzhu4 = {14, 8, 14, 8};
	__m256i fuzhu5 = {23, 17, 23, 17};
	__m256i fuzhu6 = {11, 5, 11, 5};
	__m256i fuzhu7 = {0, 4, 0, 4};
	__m256i fuzhu8 = {20, 16, 20, 16};
	__m256i fuzhu9 = {0, 20, 0, 20};

	T = _mm256_add_epi64(_mm256_sllv_epi64(Z[6], fuzhu4), _mm256_sllv_epi64(Z[8], fuzhu5));
	T = _mm256_add_epi64(T, _mm256_sllv_epi64(Z[9], fuzhu6));

	// 0xcc=> 00110011 (从低位到高位)
	E_F[4] = _mm256_add_epi64(E_F[4], _mm256_add_epi64(_mm256_and_si256(_mm256_shuffle_epi32(T, 0x4e), temp8), _mm256_blend_epi32(zero, T, 0xcc)));

	// todo
	//  Algorithm7
	__m256i fuzhu71 = {26, 52, 26, 52};
	__m256i fuzhu81 = {67108863, 4503599627370495, 67108863, 4503599627370495};
	__m256i fuzhu91 = {0, 4, 0, 4};
	__m256i fuzhu92 = {22, 16, 22, 16};

	__m256i Q, Q_1;
	H[4] = _mm256_srlv_epi64(E_F[4], fuzhu71);
	E_F[4] = _mm256_and_si256(E_F[4], fuzhu81);
	Q = _mm256_add_epi64(H[4], _mm256_shuffle_epi32(H[4], 0x4e));
	// shuf(a,a,im8) =>_mm256_shuffle_epi32(a,im8)
	Q_1 = _mm256_sub_epi64(zero, Q);
	E_F[0] = _mm256_add_epi64(E_F[0], _mm256_srlv_epi64(_mm256_blend_epi32(Q, zero, 0xcc), fuzhu91));
	E_F[1] = _mm256_add_epi64(E_F[1], _mm256_srlv_epi64(_mm256_blend_epi32(Q, Q_1, 0x33), fuzhu92));
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