#include <stdio.h>
#include <openssl/bn.h>

#define mul(r, a, word, carry)        \
    do                                \
    {                                 \
        register BN_ULONG high, low;  \
        asm("mulq %3"                 \
            : "=a"(low), "=d"(high)   \
            : "a"(word), "g"(a)       \
            : "cc");                  \
        asm("addq %2,%0; adcq %3,%1"  \
            : "+r"(carry), "+d"(high) \
            : "a"(low), "g"(0)        \
            : "cc");                  \
        (r) = carry, carry = high;    \
    } while (0)

long euclid(long a, long b, long *x, long *y)
{
    // static long q_next;
    if (b == 0)
    {
        *x = 1, *y = 0;
        return a;
    }

    int res = euclid(b, a % b, x, y);

    long t = *y;
    *y = *x - a / b * *y;
    *x = t;

    return res;
}

long inverse_mod(long b, long a)
{
    long x, y;
    euclid(a, b, &x, &y);

    if (y < 0)
    {
        y += a;
        return y % a;
    }
    else
        return y % a;
}

void mont_mul()
{
    // unsigned long R = (unsigned long)1 << 32;
    // unsigned long N = 34982313;
    // long R_inv = inverse_mod(R, N);
    // unsigned long N_1 = (R * R_inv - 1) / N;
    // unsigned long T = 482754982;
    // unsigned long m = (T * N_1) % R;
    // unsigned long t = (T + m * N) / R;
    // if (t > N)
    //     t -= N;
    // printf("%d\n", t);
    // printf("%d\n", R_inv);
    // printf("%d\n", T);

    unsigned long p_sm2[4] = {0xffffffffffffffff, 0xffffffff00000000, 0xffffffffffffffff, 0xfffffffeffffffff};
    unsigned long T[8] = {0x8427a7710155f045, 0x5b36cb4bacbc37ea, 0x87afaefcb85af546, 0x51cc03791fa78918, 0x35f31eeb82bf0f7f, 0x9adcfe0d8f645f9f, 0x64910a46ad62ce77, 0x81d21ecf1c119a4};
    unsigned long R_inv[4] = {0xfffffff900000004, 0xfffffffd00000006, 0xfffffffc00000002, 0xfffffffb00000005};
    unsigned long N_1[4] = {0x0000000000000001, 0xffffffff00000001, 0xfffffffe00000000, 0xfffffffc00000001};

    unsigned long long r, carry, borrow, carry2;

    unsigned long T2[8] = {0};
    BN_ULONG T3[8] = {0};
    BN_ULONG X[4] = {0};

    int i, j;
    for (i = 0; i < 4; i++)
    {
        // T1=T[0]

        // T2=T1*p_sm2
        carry = 0;
        for (j = 0; j < 4; j++)
        {
            mul(r, T[0], p_sm2[j], carry);
            T2[j] = r;
        }
        T2[j] = carry;
        // T3=T+T2
        carry = 0;
        for (j = 0; j < 8; j++)
        {
            T3[j] = T[j] + T2[j] + carry;
            carry = T3[j] < (T[j] + carry) ? 1 : 0;
        }
        // T3[j] = carry;

        // T=T3/2^s
        for (j = 0; j < 7 - i; j++)
        {
            T[j] = T3[j + 1];
        }
        T[j] = 0;
    }
    borrow = 0;
    for (j = 0; j < 4; j++)
    {
        X[j] = T[j] - p_sm2[j] - borrow;
        borrow = X[j] > (T[j] - borrow) ? 1 : 0;
    }
    printf("0x");
    if (borrow == 1)
    {
        // T
        for (int i = 3; i >= 0; i--)
        {
            printf("%lx", T[i]);
        }
        printf("\n");
    }
    else
    {
        // X
        for (int i = 3; i >= 0; i--)
        {
            printf("%lx", X[i]);
        }
        printf("\n");
    }
}

void mont_mul_opt()
{

    unsigned long p_sm2[10] = {0x3ffffff, 0x3ffffff, 0xfff, 0x3fc0000, 0x3ffffff, 0x3ffffff, 0x3ffffff, 0x3ffffff, 0x3feffff, 0x3fffff};
    unsigned long T[20] = {0x155f045, 0x1e9dc40, 0x37ea842, 0x12eb2f0, 0x25b36cb, 0x216bd51, 0x2faefcb, 0x224621e, 0x3791fa7, 0x3d47300, 0x2bf0f7, 0x3cc7bae, 0x5f9f35, 0x38363d9, 0x379adcf, 0x2b58b39, 0x910a46, 0x466919, 0x21ecf1c, 0x2074};
    unsigned long R_inv[10] = {0x4, 0x3fffe40, 0x6fff, 0x3f40000, 0x2ffffff, 0x0, 0x3ffffc0, 0x17ff, 0x3fb0000, 0x3fffff};
    unsigned long N_1[10] = {0x1, 0x0, 0x1000, 0x3fc0000, 0xffffff, 0x0, 0x3ffffe0, 0x7ff, 0x3fc0000, 0x3fffff};

    unsigned long T2[10] = {0};
    BN_ULONG X[10] = {0};

    int i, j;
    for (i = 0; i < 10; i++)
    {
        // 1. T1=T[i]

        // 2. T2=T1*p_sm2
        T2[2] = T[i] << 12;
        T2[3] = T[i] << 18;
        T2[8] = T[i] << 16;
        T2[9] = T[i] << 22; // 9+i

        //- 3.1 T3=T+T2
        T[i + 2] = T[i + 2] + T2[2];
        T[i + 3] = T[i + 3] - T2[3];
        T[i + 8] = T[i + 8] - T2[8];
        T[i + 9] = T[i + 9] + T2[9];

        T[i + 3] += 1UL << 44;
        T[i + 4] -= 1UL << 18;
        // T[i + 3] += 1UL << 48;
        // T[i + 4] -= 1UL << 22;
        T[i + 8] += 1UL << 42;
        T[i + 9] -= 1UL << 16;
        // T[i + 8] += 1UL << 48;
        // T[i + 9] -= 1UL << 22;

        //- 3.2 约减
        if (i < 9)
        {
            T[i + 3] = (T[i + 2] >> 26) + T[i + 3];
            T[i + 2] = T[i + 2] & 67108863;
            T[i + 4] = (T[i + 3] >> 26) + T[i + 4];
            T[i + 3] = T[i + 3] & 67108863;
            T[i + 5] = (T[i + 4] >> 26) + T[i + 5];
            T[i + 4] = T[i + 4] & 67108863;

            T[i + 9] = (T[i + 8] >> 26) + T[i + 9];
            T[i + 8] = T[i + 8] & 67108863;
            T[i + 10] = (T[i + 9] >> 26) + T[i + 10];
            T[i + 9] = T[i + 9] & 67108863;
            T[i + 11] = (T[i + 10] >> 26) + T[i + 11];
            T[i + 10] = T[i + 10] & 67108863;
        }
        else
        {
            T[i + 3] = (T[i + 2] >> 26) + T[i + 3];
            T[i + 2] = T[i + 2] & 67108863;
            T[i + 4] = (T[i + 3] >> 26) + T[i + 4];
            T[i + 3] = T[i + 3] & 67108863;
            T[i + 5] = (T[i + 4] >> 26) + T[i + 5];
            T[i + 4] = T[i + 4] & 67108863;

            T[i + 9] = (T[i + 8] >> 26) + T[i + 9];
            T[i + 8] = T[i + 8] & 67108863;
            T[i + 10] = (T[i + 9] >> 26) + T[i + 10];
            T[i + 9] = T[i + 9] & 67108863;
            // T[i + 11] = (T[i + 10] >> 26) + T[i + 11];
            // T[i + 10] = T[i + 10] & 67108863;
        }

        // 4. T=T3/2^s
    }

    for (int i = 10; i < 19; i++)
    {
        T[i + 1] = (T[i] >> 26) + T[i + 1];
        T[i] = T[i] & 67108863;
    }

    BIGNUM *T_bn = BN_new();
    BN_zero(T_bn);

    printf("0x");
    for (int i = 19; i >= 10; i--)
    {
        BN_lshift(T_bn, T_bn, 26);
        BN_add_word(T_bn, T[i]);
    }
    printf("%s", BN_bn2hex(T_bn));
    printf("\n");
}

int main()
{
    mont_mul_opt();
}