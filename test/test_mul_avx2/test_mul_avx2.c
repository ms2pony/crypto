#include <immintrin.h>
#include <stdio.h>
#include <openssl/bn.h>
//在util目录中
#include <util/bn_avx2/bn_avx2_info.h>
#include <util/bn_avx2/get_bn_avx2.h>
#include <util/bn_avx2/show_bn_avx2.h>
#include <util/bn_convert/bn_convert.h>

#define P256_LIMBS (256 / BN_BITS2)

/* Montgomery mul: res = a*b*2^-256 mod P */
void ecp_nistz256_mul_mont(BN_ULONG res[P256_LIMBS],
                           const BN_ULONG a[P256_LIMBS],
                           const BN_ULONG b[P256_LIMBS]);

int mul_avx2(__m256i E_F[5], __m256i A_B[5], __m256i C_D[5]);
// void ecp_nistz256_mul_mont(BN_ULONG res[P256_LIMBS],
//                            const BN_ULONG a[P256_LIMBS],
//                            const BN_ULONG b[P256_LIMBS]);

void test_mul_avx2()
{
    __m256i A_B[5];
    __m256i C_D[5];
    __m256i E_F[5] = {0};

    // A= 0x7c977d021722d19b7f258d720c3e068dc9126bee07a598c5f36d5bd19b10a924
    // B= 0xd1594bfffb715b36cda63c3366285f9222662ac0712ee551763baea68ade7b3
    // C= 0x379d9eb14e0f1e95635b7aeb3446af44c398ba038cd949bde99ec7de1d713ea1
    // D= 0xf1ccb5a66d36f5842b29f4b0b4f2f6e10279aaba1e745747c3188decb198c169
    //初始化A_B, C_D
    A_B[0] = _mm256_set_epi64x(15645338, 11397043, 56030310, 51423524);
    A_B[1] = _mm256_set_epi64x(45096011, 48583030, 62398102, 25976630);
    A_B[2] = _mm256_set_epi64x(26780030, 19015266, 51347875, 29954667);
    A_B[3] = _mm256_set_epi64x(5688755, 27671603, 54947324, 39376672);
    A_B[4] = _mm256_set_epi64x(214373, 12582839, 2041311, 16914210);

    C_D[0] = _mm256_set_epi64x(35879724, 26788201, 61994887, 24198817);
    C_D[1] = _mm256_set_epi64x(48789969, 24411185, 930661, 10215065);
    C_D[2] = _mm256_set_epi64x(20757944, 16939434, 17935313, 12818618);
    C_D[3] = _mm256_set_epi64x(64360620, 43993867, 8017293, 28815027);
    C_D[4] = _mm256_set_epi64x(3961645, 27684150, 911207, 45174287);

    // E=A*C=0x1b1141fee722e7f5dc7803407348be0dc5629b9c27765ce3322d17e08cf79956cabd2cd23296eead068bb431dde56ab8779b0ae99dda6d3b6e3f811c4b5517a4
    //  =0x35b5ef0dfa2db43e27bf8049492a55d1f8622e601b1ad0cde16ea6b427f3d9d3
    // F=B*D=0xc5bc7840c7a550f009660c9fbd63735499c306f4ad15329085953b39876df2ae9921bb9c455cc9e703016ff0ea4a48b942ab7902ed28a2c3017f7886049fb6b
    //  =0x55b102d926c819a0e0c9af0938bb01e08c16dc8680f1a174faf79ff9c436e3d1
    mul_avx2(E_F, A_B, C_D);

    int size[20];
    limb_size(E_F, size);
    show_bn_avx2(E_F, size);
    //分别打印E_F中两个大数的10个limb的值(从低位到高位)
    show_bn_avx2_py(E_F);
}

void test_mul_avx2_2()
{
    __m256i A_B[5];
    __m256i C_D[5];
    __m256i E_F[5] = {0};

    unsigned int seed = (unsigned int)time(NULL);

    for (int i = 0; i < 15; i++)
    {

        get_bn_avx2(A_B, seed++);
        show_bn_avx2_2(A_B);

        get_bn_avx2(C_D, seed++);
        show_bn_avx2_2(C_D);

        mul_avx2(E_F, A_B, C_D);

        show_bn_avx2_2(E_F);
    }
}

void test_mul_avx2_3()
{
    __m256i A_B[5];
    __m256i C_D[5];
    __m256i E_F[5] = {0};
    BN_ULONG A[5] = {0}, B[5] = {0}, C[5] = {0}, D[5] = {0}, E[5] = {0}, F[5] = {0};

    BIGNUM *bn_A = BN_new();
    BIGNUM *bn_B = BN_new();
    BIGNUM *bn_C = BN_new();
    BIGNUM *bn_D = BN_new();

    BIGNUM *bn_E = BN_new();
    BIGNUM *bn_F = BN_new();

    unsigned int seed = (unsigned int)time(NULL);

    // for (int i = 0; i < 15; i++)
    // {

    get_bn_avx2(A_B, seed++);
    show_bn_avx2_hex(A_B, "A", "B");

    get_bn_avx2(C_D, seed++);
    show_bn_avx2_hex(C_D, "C", "D");

    mul_avx2(E_F, A_B, C_D);
    show_bn_avx2_hex(E_F, "E", "F");

    //利用python计算A*C%p，B*D%p，得到E,F，与mul_avx2函数得到的E,F进行比较
    //如果相等则mul_avx2功能正确，
    //注意mul_avx2得到的E、F还要分别与p取模，因为E,F长度可能大于256-bit

    // }
}

void test_mul_avx2_4()
{
    __m256i A_B[5];
    __m256i C_D[5];
    __m256i E_F[5];

    unsigned int seed = (unsigned int)time(NULL);

    //利用openssl中的BN_mod_mul函数来检验mul_avx2函数是否能得到正确结果
    BN_CTX *bn_ctx = BN_CTX_new();

    BIGNUM *r = BN_new(), *a = BN_new(), *b = BN_new(), *m = BN_new();
    BIGNUM *r2 = BN_new(), *c = BN_new(), *d = BN_new();

    BN_hex2bn(&m, "fffffffeffffffffffffffffffffffffffffffff00000000ffffffffffffffff");

    get_bn_avx2(A_B, seed++);
    show_bn_avx2_hex(A_B, "A", "B");

    get_bn_avx2(C_D, seed++);
    show_bn_avx2_hex(C_D, "C", "D");

    avx2to_bignum(A_B, a, b);
    avx2to_bignum(C_D, c, d);

    mul_avx2(E_F, A_B, C_D);
    show_bn_avx2_hex2(E_F, "E", "F");

    BN_mod_mul(r, a, c, m, bn_ctx);
    BN_mod_mul(r2, b, d, m, bn_ctx);
    printf("E2 = \t%s\n", BN_bn2hex(r));
    printf("F2 = \t%s\n", BN_bn2hex(r2));
}

int main()
{
    test_mul_avx2_2();
    // test_mul_avx2_4();
    return 0;
}