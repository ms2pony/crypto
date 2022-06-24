/**
 * @require 需要openssl库
 * @brief 1. 测试unsigned char *类型到openssl的BIGNUM类型的转换，对应BN_lebin2bn函数
 * 2. BN_lebin2bn函数、ecp_nistz256_mul_mont函数、ecp_nistz256_mul_mont函数的使用
 * 2.1. BN_lebin2bn函数转换前的类型可以用于ecp_nistz256_mul_mont函数
 * 2.2. BN_lebin2bn函数转换后的类型可以用于ecp_nistz256_mul_mont函数
 *
 */

#define P256_LIMBS (256 / BN_BITS2)
#include <openssl/bn.h>
#include <stdint.h>

/* Montgomery mul: res = a*b*2^-256 mod P */
void ecp_nistz256_mul_mont(BN_ULONG res[P256_LIMBS],
						   const BN_ULONG a[P256_LIMBS],
						   const BN_ULONG b[P256_LIMBS]);

int main()
{

	// int res = array2BnTest();
	// printf("res=%d\n", res);

	BN_ULONG a[4] = {319875643198, 323298, 3232879827, 23239823};
	BN_ULONG b[4] = {12212165412, 998872324, 5161623123, 65165123};
	BN_ULONG res[4] = {0, 0, 0, 0};

	BIGNUM *bn_a = BN_new();
	BIGNUM *bn_b = BN_new();
	BIGNUM *bn_res = BN_new();
	BIGNUM *bn_p256 = BN_new();
	BIGNUM *bn_R = BN_new();
	BIGNUM *bn_R_inv = BN_new();
	BN_MONT_CTX *mont_ctx = BN_MONT_CTX_new();
	BN_CTX *bn_ctx = BN_CTX_new();

	BN_hex2bn(&bn_p256, "ffffffff00000001000000000000000000000000ffffffffffffffffffffffff");

	BN_MONT_CTX_set(mont_ctx, bn_p256, bn_ctx);

	BN_lebin2bn((unsigned char *)a, 32, bn_a);
	BN_lebin2bn((unsigned char *)b, 32, bn_b);

	printf("a:\t%s\n", BN_bn2hex(bn_a));
	printf("b:\t%s\n", BN_bn2hex(bn_b));

	ecp_nistz256_mul_mont(res, a, b);
	BN_lebin2bn((unsigned char *)res, 32, bn_res);

	printf("res1 = a*b*2^-256 mod P\n=\t%s\n", BN_bn2hex(bn_res));

	BN_set_bit(bn_R, 256);
	BN_mod_inverse(bn_R_inv, bn_R, bn_p256, bn_ctx);
	printf("R_inv = \n\t%s\n", BN_bn2hex(bn_R_inv));
	res[0] = 0;
	BN_mod_mul_montgomery(bn_res, bn_a, bn_b, mont_ctx, bn_ctx);
	printf("res2 = a*b*2^-256 mod P\n=\t%s\n", BN_bn2hex(bn_res));

	return 0;
}