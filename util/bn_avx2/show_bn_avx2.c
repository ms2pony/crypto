#include <util/bn_avx2/show_bn_avx2.h>
#include <util/bn_avx2/get_bn_avx2.h>
#include <util/bn_avx2/bn_avx2_info.h>
#include <util/bn_convert/bn_convert.h>

/**
 * @brief 打印出的A_B兼容python的字典
 *
 * @param A_B
 * @require
 */
void show_bn_avx2_2(__m256i A_B[5])
{
	printf("{\"A\":[");
	for (int i = 0; i < 5; i++)
	{
		printf("%llu,", A_B[i][0]);
		if (i < 4)
		{
			printf("%llu,", A_B[i][1]);
		}
		else
		{
			printf("%llu", A_B[i][1]);
		}
	}
	// printf("]}\n");
	printf("],\n");

	printf("\"B\":[");
	for (int i = 0; i < 5; i++)
	{
		printf("%llu,", A_B[i][2]);
		if (i < 4)
		{
			printf("%llu,", A_B[i][3]);
		}
		else
		{
			printf("%llu", A_B[i][3]);
		}
	}
	printf("]}\n");
}

void show_bn_avx2(__m256i A_B[5], int size[20])
{
	printf("A:  ");
	for (int i = 0; i < 5; i++)
	{
		printf("%16llx  ", A_B[i][0]);
		printf("%16llx  ", A_B[i][1]);
	}
	printf("\n");

	printf("    ");
	for (int i = 0; i < 10; i++)
	{
		printf("%16d  ", size[i]);
	}
	printf("\n");

	printf("B:  ");
	for (int i = 0; i < 5; i++)
	{
		printf("%16llx  ", A_B[i][2]);
		printf("%16llx  ", A_B[i][3]);
	}
	printf("\n");

	printf("    ");
	for (int i = 10; i < 20; i++)
	{
		printf("%16d  ", size[i]);
	}
	printf("\n");
}

void show_bn_avx2_py(__m256i A_B[5])
{
	printf("E=[");
	for (int i = 0; i < 5; i++)
	{
		printf("0x%llx,", A_B[i][0]);
		if (i < 4)
		{
			printf("0x%llx,", A_B[i][1]);
		}
		else
		{
			printf("0x%llx", A_B[i][1]);
		}
	}
	printf("]\n");

	printf("F=[");
	for (int i = 0; i < 5; i++)
	{
		printf("0x%llx,", A_B[i][2]);
		if (i < 4)
		{
			printf("0x%llx,", A_B[i][3]);
		}
		else
		{
			printf("0x%llx", A_B[i][3]);
		}
	}
	printf("]\n");
}

/**
 * @brief 将avx2形式的两个大数以字符串形式打印出来
 *
 * @param A_B
 * @require
 */
void show_bn_avx2_hex(__m256i A_B[5], char *s1, char *s2)
{
	BIGNUM *bn_A = BN_new();
	BIGNUM *bn_B = BN_new();
	avx2to_bignum(A_B, bn_A, bn_B);

	printf("%s = \t%s\n", s1, BN_bn2hex(bn_A));
	printf("%s = \t%s\n", s2, BN_bn2hex(bn_B));
}

/**
 * @brief 在show_bn_avx2_hex函数的基础上会对两个大数进行取模
 *
 * @param A_B
 * @require
 */
void show_bn_avx2_hex2(__m256i A_B[5], char *s1, char *s2)
{
	BIGNUM *bn_A = BN_new();
	BIGNUM *bn_B = BN_new();
	BIGNUM *bn_p256 = BN_new();
	BN_CTX *bn_ctx = BN_CTX_new();

	BN_hex2bn(&bn_p256, "fffffffeffffffffffffffffffffffffffffffff00000000ffffffffffffffff");

	avx2to_bignum(A_B, bn_A, bn_B);

	BN_mod(bn_A, bn_A, bn_p256, bn_ctx);
	BN_mod(bn_B, bn_B, bn_p256, bn_ctx);

	printf("%s = \t%s\n", s1, BN_bn2hex(bn_A));
	printf("%s = \t%s\n", s2, BN_bn2hex(bn_B));
}