#include <stdio.h>
#include <openssl/bn.h>

unsigned long T[20] = {0x155f045, 0x1e9dc40, 0x37ea842, 0x12eb2f0, 0x25b36cb, 0x216bd51, 0x2faefcb, 0x224621e, 0x3791fa7, 0x3d47300, 0x2bf0f7, 0x3cc7bae, 0x5f9f35, 0x38363d9, 0x379adcf, 0x2b58b39, 0x910a46, 0x466919, 0x21ecf1c, 0x2074};

void mont_mul_opt(unsigned long **res)
{
    //-算出约减阶段最长依赖T9
    unsigned long t0,t1,t2,t3,t4,t5,t6,t7,t8,t9;
    unsigned long T0,T1,T2,T3,T4,T5,T6,T7,T8,T9;
    unsigned long T3_1,T4_1,T5_1,T6_1,T7_1,T8_1,T9_1;

    t0=T[0];t1=T[1];
    t2=T[2]+(t0<<12);t3=T[3]-(t0<<18)+(t1<<12);
    T2=t2&67108863;T3_1=t3+(t2>>26);
    T3=T3_1&67108863;t4=T[4]-(t1<<18)+(T2<<12);
    t5=T[5]-(T2<<18)+(T3<<12);T4_1=t4+(T3_1>>26);
    T4=T4_1&67108863;T5_1=t5+(T4_1>>26);
    T5=T5_1&67108863;t6=T[6]-(T3<<18)+(T4<<12);
    t7=T[7]-(T4<<18)+(T5<<12);T6_1=t6+(T5_1>>26);
    T6=T6_1&67108863;T7_1=t7+(T6_1>>26);
    T7=T7_1&67108863;t8=T[8]-(t0<<16)-(T5<<18)+(T6<<12);
    t9=T[9]+(t0<<22)-(t1<<16)-(T6<<18)+(T7<<12);T8_1=t8+(T7_1>>26);
    T8=T8_1&67108863;T9_1=t9+(T8_1>>26);
    T9=T9_1&67108863;

    //计算结果R的R8
    T[18]+=T9<<22;

    //digit size reduction阶段
    // for (int i = 11; i < 19; i++)
    // {
    //     T[i + 1] = (T[i] >> 26) + T[i + 1];
    //     T[i] = T[i] & 67108863;
    // }

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
