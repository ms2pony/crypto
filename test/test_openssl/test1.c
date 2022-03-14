//测试ecp_nistz256_mul_montx的执行过程
// #define BN_ULONG unsigned long
#define P256_LIMBS (256 / BN_BITS2)
// #define BN_BITS2 64
#include <openssl/bn.h>
#include <stdint.h>
#include <u1.h>

/* Montgomery mul: res = a*b*2^-256 mod P */
void ecp_nistz256_mul_mont(BN_ULONG res[P256_LIMBS],
						   const BN_ULONG a[P256_LIMBS],
						   const BN_ULONG b[P256_LIMBS]);

int array2BnTest()
{
	BIGNUM *bn_a;
	bn_a = BN_new();
	BN_ULONG a[4] = {319875643198, 323298, 3232879827, 2123223239823};
	array2Bn(bn_a, a, 4);
	char *hex_a = BN_bn2hex(bn_a);

	BIGNUM *bn_b = BN_new();
	BN_hex2bn(&bn_b, hex_a);

	// BN_cmp(bn_b, bn_a)返回0，表示相等
	// 证明array2Bn函数的功能能够正确执行
	if (BN_cmp(bn_b, bn_a) == 0)
		return 1;

	return 0;
}

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

	array2Bn(bn_a, a, 4);
	array2Bn(bn_b, b, 4);
	array2Bn(bn_res, res, 4);

	printf("a:\t%s\n", BN_bn2dec(bn_a));
	printf("b:\t%s\n", BN_bn2dec(bn_b));
	printf("res0 = %s\n", BN_bn2dec(bn_res));

	ecp_nistz256_mul_mont(res, a, b);

	printf("res1 = a*b*2^-256 mod P\n=\t%s\n", BN_bn2dec(bn_res));

	BN_set_bit(bn_R, 256);
	BN_mod_inverse(bn_R_inv, bn_a, bn_p256, bn_ctx);
	res[0] = 0;
	BN_mod_mul_montgomery(bn_res, bn_a, bn_b, mont_ctx, bn_ctx);
	printf("res2 = a*b*2^-256 mod P\n=\t%s\n", BN_bn2dec(bn_res));

	return 0;
}