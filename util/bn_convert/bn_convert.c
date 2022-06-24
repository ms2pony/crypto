#include <util/bn_convert/bn_convert.h>
#include <openssl/bn.h>

void bn_avx2to_normal(__m256i A_B[5], BN_ULONG A[5], BN_ULONG B[5])
{
	if (A_B[4][1] >> 22)
	{
		A[4] = A_B[4][1] >> 22;
	}

	if (A_B[4][3] >> 22)
	{
		B[4] = A_B[4][3] >> 22;
	}

	A[3] = (A_B[4][1] << 42) + (A_B[4][0] << 16) + (A_B[3][1] >> 10);
	B[3] = (A_B[4][3] << 42) + (A_B[4][2] << 16) + (A_B[3][3] >> 10);

	A[2] = (A_B[3][1] << 54) + (A_B[3][0] << 28) + (A_B[2][1] << 2) + (A_B[2][0] >> 24);
	B[2] = (A_B[3][3] << 54) + (A_B[3][2] << 28) + (A_B[2][3] << 2) + (A_B[2][2] >> 24);

	A[1] = (A_B[2][0] << 40) + (A_B[1][1] << 14) + (A_B[1][0] >> 12);
	B[1] = (A_B[2][2] << 40) + (A_B[1][3] << 14) + (A_B[1][2] >> 12);

	A[0] = (A_B[1][0] << 52) + (A_B[0][1] << 26) + A_B[0][0];
	B[0] = (A_B[1][2] << 52) + (A_B[0][3] << 26) + A_B[0][2];
}

void normal2bignum(BN_ULONG A[], int size, BIGNUM *bn_A)
{
	// limb为64-bit长
	BN_lebin2bn((unsigned char *)A, size * 8, bn_A);
}

void avx2to_bignum(__m256i A_B[5], BIGNUM *bn_A, BIGNUM *bn_B)
{
	BN_ULONG A[5] = {0}, B[5] = {0};

	bn_avx2to_normal(A_B, A, B);
	normal2bignum(A, 5, bn_A);
	normal2bignum(B, 5, bn_B);
}

static void test_bn_avx2to_normal()
{
	BIGNUM *bn_A = BN_new(), *bn_B = BN_new();
	BN_ULONG A[5] = {0}, B[5] = {0};
	__m256i A_B[5] = {0};
	get_bn_avx2(A_B, 32923);
	bn_avx2to_normal(A_B, A, B);

	//利用python算出A_B中的A,B，然后与下面的A，B比较是否相同
	show_bn_avx2_py(A_B);

	BN_lebin2bn((unsigned char *)A, 40, bn_A);
	BN_lebin2bn((unsigned char *)B, 40, bn_B);
	printf("A = \t%s\n", BN_bn2hex(bn_A));
	printf("B = \t%s\n", BN_bn2hex(bn_B));
}

// int main()
// {
// 	test_bn_avx2to_normal();
// }