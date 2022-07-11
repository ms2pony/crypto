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

	/**
	 * @brief Algorithm5的实现代码
	 * 计算A*C和B*D，并将结果存入临时变量Z[10]
	 */
	__m256i C_D1[5];	 // C_D的数据经过_mm256_alignr_epi8函数处理后放入C_D1
	__m256i Z[10] = {0}; //辅助变量，初始化时，所有元素都需要为0
	__m256i U, V;		 // A_B的数据经过_mm256_shuffle_epi32函数处理后放入U和V

	__m256i W;
	__m256i zero_v = {0}; // 4个元素值都为0的__m256i变量

	//预处理，_mm256_alignr_epi8函数处理C_D得到C_D1
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
		U = _mm256_shuffle_epi32(A_B[i], 0x44);
		for (int j = 0; j < 5; j++)
		{
			W = _mm256_mul_epu32(U, C_D[j]); // [ A[2i]*C[2j], A[2i]*C[2j+1], B[2i]*C[2j], B[2i]*C[2j+1] ]
			Z[i + j] = _mm256_add_epi64(Z[i + j], W);
		}

		// 0xEE=>11101110b=>23 23(四进制，从左到右是对应从低位到高位)
		// V[i]=[A[2i+1],A[2i+1],B[2i+1],B[2i+1]]
		V = _mm256_shuffle_epi32(A_B[i], 0xEE);
		for (int j = 0; j < 4; j++)
		{
			W = _mm256_mul_epu32(V, C_D1[j]); // [ A[2i+1]*C[2j+1], A[2i+1]*C[2j+2], B[2i+1]*D[2j+1], B[2i+1]*D[2j+2] ]
			Z[i + j + 1] = _mm256_add_epi64(Z[i + j + 1], W);
		}

		// W = MUL(V,<C,D>_{4})
		// C_D1[4] = [ C[9], C[0], D[9], D[0] ], V[i]=[ A[2i+1], A[2i+1], B[2i+1], B[2i+1] ]
		// V[i]*C_D1[4]=[ C[9]*A[2i+1], C[0]*A[2i+1], D[9]*B[2i+1], D[0]*B[2i+1] ]
		W = _mm256_mul_epu32(V, C_D1[4]);

		Z[i] = _mm256_add_epi64(Z[i], _mm256_blend_epi32(W, zero_v, 0x33));
		Z[i + 5] = _mm256_add_epi64(Z[i + 5], _mm256_blend_epi32(W, zero_v, 0xcc));
	}

	/**
	 * @brief Algorithm6的实现代码
	 * A*C和B*D的结果存放在Z中，而Z中的元素能够达到60-bit长
	 * Algorithm6将Z[4]至Z[8]中的元素的长度缩短至最多28-bit长
	 * Z[9]缩短至最多30-bit长
	 */
	__m256i L[10], M[10], H[10] = {0}, M_1[10];											 // M_1 为 M^{\prime}
	__m256i con1 = {0x3ffffff, 0x3ffffff, 0x3ffffff, 0x3ffffff};						 // 需要用到的常数，67108863=2^{n^{\prime}}-1,n^{\prime}=26
	__m256i con2 = {52, 52, 52, 52};													 // 需要用到的常数，2n^{\prime}=52
	__m256i con3 = {26, 26, 26, 26};													 // 需要用到的常数，n^{\prime}=26
	__m256i mask = {0xfffffffffffff, 0xfffffffffffff, 0xfffffffffffff, 0xfffffffffffff}; // 需要用到的常数

	for (int i = 4; i < 9; i++)
	{
		L[i] = _mm256_and_si256(Z[i], con1);
		M[i] = _mm256_srli_epi64(Z[i], 26);
		M[i] = _mm256_and_si256(M[i], con1);
		H[i] = _mm256_srli_epi64(Z[i], 52);
	}

	L[9] = _mm256_and_si256(Z[9], con1);
	M[9] = _mm256_srli_epi64(Z[9], 26);

	for (int i = 5; i < 10; i++)
	{
		// M_1[i]=[ M[2i-1], M[2i],... ]
		M_1[i] = _mm256_alignr_epi8(M[i], M[i - 1], 8);

		// L[i]=[ L[2i], L[2i+1],... ]
		Z[i] = _mm256_add_epi64(_mm256_add_epi64(L[i], M_1[i]), H[i - 1]);
	}

	Z[4] = _mm256_blend_epi32(_mm256_and_si256(Z[4], mask), L[4], 0xcc);

	/**
	 * @brief Algorithm8的实现代码
	 * 使用梅森素数约减法对Z中的A*C和B*D的结果进行约减
	 */
	__m256i con4 = {15, 1, 15, 1}; // SHLV
	__m256i con5 = {4, 22, 4, 22}; // SHLV
	__m256i con6 = {0, -1, 0, -1}; //[111..1,0,11..1,0]

	__m256i con7 = {0, 10, 0, 10};
	__m256i con8 = {1, 24, 1, 24};
	__m256i con9 = {23, 2, 23, 2};

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
	E_F[0] = _mm256_add_epi64(E_F[0], _mm256_sllv_epi64(_mm256_blend_epi32(_mm256_permute4x64_epi64(Z[9], 0xb1), Z[8], 0xcc), con4));

	// E_F[1]
	Z_1[8] = _mm256_sub_epi64(zero_v, Z[8]);
	Z_1[9] = _mm256_sub_epi64(zero_v, Z[9]);
	E_F[1] = _mm256_sub_epi64(Z[1], _mm256_slli_epi64(Z[5], 16));

	// 0xcc=> 00110011 (从低位到高位), 0xb1=>1 0 3 2 (从低位到高位)
	E_F[1] = _mm256_add_epi64(E_F[1], _mm256_sllv_epi64(_mm256_blend_epi32(Z[6], _mm256_permute4x64_epi64(Z[5], 0xb1), 0xcc), con5));
	E_F[1] = _mm256_sub_epi64(E_F[1], _mm256_sllv_epi64(_mm256_and_si256(_mm256_shuffle_epi32(Z[6], 0x4e), con6), con7));
	E_F[1] = _mm256_add_epi64(E_F[1], _mm256_slli_epi64(_mm256_blend_epi32(Z[8], Z_1[8], 0xcc), 12));
	// SHUF(a,b,0x5) => blend(shuf(a,0xb1),shuf(b,0xb1),0xcc)
	E_F[1] = _mm256_add_epi64(E_F[1], _mm256_slli_epi64(_mm256_blend_epi32(_mm256_shuffle_epi32(Z[8], 0x4e), _mm256_shuffle_epi32(Z_1[9], 0x4e), 0xcc), 6));
	E_F[1] = _mm256_add_epi64(E_F[1], _mm256_sllv_epi64(_mm256_blend_epi32(Z[9], Z[7], 0xcc), con8)); // 14

	E_F[2] = _mm256_add_epi64(Z[2], _mm256_slli_epi64(_mm256_blend_epi32(_mm256_shuffle_epi32(Z[5], 0x4e), _mm256_shuffle_epi32(Z[6], 0x4e), 0xcc), 22));
	E_F[2] = _mm256_add_epi64(E_F[2], _mm256_slli_epi64(Z[7], 4));
	E_F[2] = _mm256_add_epi64(E_F[2], _mm256_slli_epi64(Z[8], 24));
	E_F[2] = _mm256_add_epi64(E_F[2], _mm256_slli_epi64(_mm256_blend_epi32(_mm256_shuffle_epi32(Z[8], 0x4e), _mm256_shuffle_epi32(Z[9], 0x4e), 0xcc), 19));
	E_F[2] = _mm256_add_epi64(E_F[2], _mm256_slli_epi64(Z[9], 12));
	E_F[2] = _mm256_add_epi64(E_F[2], _mm256_slli_epi64(_mm256_blend_epi32(_mm256_shuffle_epi32(Z[9], 0x4e), zero_v, 0xcc), 6));

	E_F[3] = _mm256_add_epi64(Z[3], _mm256_slli_epi64(_mm256_blend_epi32(_mm256_shuffle_epi32(Z[6], 0x4e), _mm256_shuffle_epi32(Z[7], 0x4e), 0xcc), 22));
	E_F[3] = _mm256_add_epi64(E_F[3], _mm256_slli_epi64(Z[8], 4));
	E_F[3] = _mm256_add_epi64(E_F[3], _mm256_slli_epi64(Z[9], 24));
	E_F[3] = _mm256_add_epi64(E_F[3], _mm256_slli_epi64(_mm256_blend_epi32(_mm256_shuffle_epi32(Z[9], 0x4e), zero_v, 0xcc), 19));

	// 0xcc=> 00110011 (从低位到高位)
	E_F[4] = _mm256_add_epi64(Z[4], _mm256_slli_epi64(Z[5], 20));
	E_F[4] = _mm256_add_epi64(E_F[4], _mm256_sllv_epi64(_mm256_permute4x64_epi64(Z[7], 0xb1), con9));

	E_F[4] = _mm256_add_epi64(E_F[4], _mm256_slli_epi64(Z[9], 4));

	__m256i T;
	__m256i con10 = {14, 8, 14, 8};
	__m256i con11 = {23, 17, 23, 17};
	__m256i con12 = {11, 5, 11, 5};
	__m256i con13 = {0, 4, 0, 4};
	__m256i con14 = {20, 16, 20, 16};
	__m256i con15 = {20, 0, 20, 0};

	T = _mm256_add_epi64(_mm256_sllv_epi64(Z[6], con10), _mm256_sllv_epi64(Z[8], con11));
	T = _mm256_add_epi64(T, _mm256_sllv_epi64(Z[9], con12));
	E_F[4] = _mm256_add_epi64(E_F[4], _mm256_add_epi64(_mm256_and_si256(_mm256_shuffle_epi32(T, 0x4e), con6), _mm256_blend_epi32(zero_v, T, 0xcc)));

	/**
	 * @brief Algorithm7的实现代码
	 * Algorithm8使用梅森素数约减法将Z中两个数进行约减并存入E_F中
	 * 但E_F中的元素长度可达60-bit，
	 * Algorithm7将E_F中的元素长度缩减为28-bit
	 */
	__m256i con16 = {52, 26, 52, 26};
	__m256i con17 = {4503599627370495, 67108863, 4503599627370495, 67108863};
	__m256i con18 = {4, 0, 4, 0};
	__m256i con19 = {16, 22, 16, 22};

	__m256i Q, Q1;
	H[4] = _mm256_srlv_epi64(E_F[4], con16);

	E_F[4] = _mm256_and_si256(E_F[4], con17); //前26位与前52位
	Q = _mm256_add_epi64(H[4], _mm256_shuffle_epi32(H[4], 0x4e));
	// shuf(a,a,im8) =>_mm256_shuffle_epi32(a,im8)
	Q1 = _mm256_sub_epi64(zero_v, Q);
	// 0xcc正，等价 +2^{4} 运算
	E_F[0] = _mm256_add_epi64(E_F[0], _mm256_sllv_epi64(_mm256_blend_epi32(Q, zero_v, 0xcc), con18));

	// 0x33反，等价 +2^{100}-2^{68} 运算
	E_F[1] = _mm256_add_epi64(E_F[1], _mm256_sllv_epi64(_mm256_blend_epi32(Q, Q1, 0x33), con19));
	//等价 +2^{228} 运算
	E_F[4] = _mm256_add_epi64(E_F[4], _mm256_sllv_epi64(_mm256_blend_epi32(Q, zero_v, 0xcc), con15));

	for (int i = 0; i < 5; i++)
	{
		L[i] = _mm256_and_si256(E_F[i], con1); // temp=4个2^26-1
		M[i] = _mm256_srlv_epi64(E_F[i], con3);
		M[i] = _mm256_and_si256(M[i], con1); //右移26再与2^26-1
		H[i] = _mm256_srlv_epi64(E_F[i], con2);
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
			// M_1[0]=[ M[2*4+1], M[2*0], ... ]=[ M[9], M[0], ... ]
			M_1[0] = _mm256_alignr_epi8(M[0], M[4], 8);
			E_F[0] = _mm256_add_epi64(_mm256_add_epi64(L[0], M_1[0]), H[4]);
		}
	}

	return 0;
}