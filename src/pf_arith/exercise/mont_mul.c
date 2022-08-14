#include <stdio.h>

#define BN_ULONG unsigned long
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

int main()
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
        // T[0]

        unsigned long Y = T[0];

        // T2=Y*p_sm2
        carry = 0;
        for (j = 0; j < 4; j++)
        {
            mul(r, Y, p_sm2[j], carry);
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
            printf("%llx", T[i]);
        }
        printf("\n");
    }
    else
    {
        // X
        for (int i = 3; i >= 0; i--)
        {
            printf("%llx", X[i]);
        }
        printf("\n");
    }
}