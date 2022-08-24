#include <stdio.h>
#include <openssl/bn.h>

unsigned long T[20] = {0x155f045, 0x1e9dc40, 0x37ea842, 0x12eb2f0, 0x25b36cb, 0x216bd51, 0x2faefcb, 0x224621e, 0x3791fa7, 0x3d47300, 0x2bf0f7, 0x3cc7bae, 0x5f9f35, 0x38363d9, 0x379adcf, 0x2b58b39, 0x910a46, 0x466919, 0x21ecf1c, 0x2074};

void mont_mul_opt(unsigned long **res)
{
    unsigned long T2[10] = {0};

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
        T[i + 8] += 1UL << 42;
        T[i + 9] -= 1UL << 16;

        //- 3.2 compress or digit size reduction
        if (i > 0)
        {
            T[i + 2] = (T[i + 1] >> 26) + T[i + 2];
            T[i + 1] = T[i + 1] & 67108863;
        }

        // 4. T=T3/2^s
    }

    for (int i = 11; i < 19; i++)
    {
        T[i + 1] = (T[i] >> 26) + T[i + 1];
        T[i] = T[i] & 67108863;
    }

    *res = T;
}

// int main()
// {
//     unsigned long *res = NULL;
//     mont_mul_opt(&res);
//     res;

//     BIGNUM *T_bn = BN_new();
//     BN_zero(T_bn);

//     printf("0x");
//     for (int i = 19; i >= 10; i--)
//     {
//         BN_lshift(T_bn, T_bn, 26);
//         BN_add_word(T_bn, res[i]);
//     }
//     printf("%s", BN_bn2hex(T_bn));
//     printf("\n");
// }
