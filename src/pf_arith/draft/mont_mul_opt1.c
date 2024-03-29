#include <stdio.h>
#include <immintrin.h>

unsigned long A[10] = {20982470, 65953693, 21914385, 49174405, 41543558, 1762678, 11052767, 48579851, 51383560, 3310613};

unsigned long B[10] = {3951798, 29668248, 30574297, 56605851, 49742749, 11577614, 57596360, 61420814, 7397846, 757517};

unsigned long T[10] = {0};

void mont_mul_opt(unsigned long **res)
{
    //-算出约减阶段最长依赖T9
    unsigned long t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18;
    unsigned long T0,T1,T2,T3,T4,T5,T6,T7,T8,T9;
    unsigned long T1_1,T2_1,T3_1,T4_1,T5_1,T6_1,T7_1,T8_1,T9_1;
    unsigned long T_1[19];

    T_1[0]=A[0]*B[0];   // step1
    t0=T_1[0];          // step2
    T0=t0&67108863;     
    T_1[1]=A[0]*B[1]+A[1]*B[0];
    t1=T_1[1];
    T1_1=t1+(t0>>26);
    T1=T1_1&67108863;
    T_1[2]=A[0]*B[2]+A[1]*B[1]+A[2]*B[0];
    t2=T_1[2]+(T0<<12);
    T2_1=t2+(T1_1>>26);
    T2=T2_1&67108863;
    T_1[3]=A[0]*B[3]+A[1]*B[2]+A[2]*B[1]+A[3]*B[0];
    t3=T_1[3]-(T0<<18)+(T1<<12);
    T3_1=t3+(T2_1>>26);
    T3=T3_1&67108863;
    T_1[4]=A[0]*B[4]+A[1]*B[3]+A[2]*B[2]+A[3]*B[1]+A[4]*B[0];
    t4=T_1[4]-(T1<<18)+(T2<<12);
    T4_1=t4+(T3_1>>26);
    T4=T4_1&67108863;
    T_1[5]=A[0]*B[5]+A[1]*B[4]+A[2]*B[3]+A[3]*B[2]+A[4]*B[1]+A[5]*B[0];
    t5=T_1[5]-(T2<<18)+(T3<<12);
    T5_1=t5+(T4_1>>26);
    T5=T5_1&67108863;
    T_1[6]=A[0]*B[6]+A[1]*B[5]+A[2]*B[4]+A[3]*B[3]+A[4]*B[2]+A[5]*B[1]+A[6]*B[0];
    t6=T_1[6]-(T3<<18)+(T4<<12);
    T6_1=t6+(T5_1>>26);
    T6=T6_1&67108863;
    T_1[7]=A[0]*B[7]+A[1]*B[6]+A[2]*B[5]+A[3]*B[4]+A[4]*B[3]+A[5]*B[2]+A[6]*B[1]+A[7]*B[0];
    t7=T_1[7]-(T4<<18)+(T5<<12);
    T7_1=t7+(T6_1>>26);
    T7=T7_1&67108863;
    T_1[8]=A[0]*B[8]+A[1]*B[7]+A[2]*B[6]+A[3]*B[5]+A[4]*B[4]+A[5]*B[3]+A[6]*B[2]+A[7]*B[1]+A[8]*B[0];
    t8=T_1[8]-(T0<<16)-(T5<<18)+(T6<<12);
    T8_1=t8+(T7_1>>26);
    T8=T8_1&67108863;
    T_1[9]=A[0]*B[9]+A[1]*B[8]+A[2]*B[7]+A[3]*B[6]+A[4]*B[5]+A[5]*B[4]+A[6]*B[3]+A[7]*B[2]+A[8]*B[1]+A[9]*B[0];
    t9=T_1[9]+(T0<<22)-(T1<<16)-(T6<<18)+(T7<<12);
    T9_1=t9+(T8_1>>26);
    T9=T9_1&67108863;
    T_1[10]=A[1]*B[9]+A[2]*B[8]+A[3]*B[7]+A[4]*B[6]+A[5]*B[5]+A[6]*B[4]+A[7]*B[3]+A[8]*B[2]+A[9]*B[1];
    t10=T_1[10]+(T1<<22)-(T2<<16)-(T7<<18)+(T8<<12);
    T_1[11]=A[2]*B[9]+A[3]*B[8]+A[4]*B[7]+A[5]*B[6]+A[6]*B[5]+A[7]*B[4]+A[8]*B[3]+A[9]*B[2];
    t11=T_1[11]+(T2<<22)-(T3<<16)-(T8<<18)+(T9<<12);
    T_1[12]=A[3]*B[9]+A[4]*B[8]+A[5]*B[7]+A[6]*B[6]+A[7]*B[5]+A[8]*B[4]+A[9]*B[3];
    t12=T_1[12]+(T3<<22)-(T4<<16)-(T9<<18);
    T_1[13]=A[4]*B[9]+A[5]*B[8]+A[6]*B[7]+A[7]*B[6]+A[8]*B[5]+A[9]*B[4];
    t13=T_1[13]+(T4<<22)-(T5<<16);
    T_1[14]=A[5]*B[9]+A[6]*B[8]+A[7]*B[7]+A[8]*B[6]+A[9]*B[5];
    t14=T_1[14]+(T5<<22)-(T6<<16);
    T_1[15]=A[6]*B[9]+A[7]*B[8]+A[8]*B[7]+A[9]*B[6];
    t15=T_1[15]+(T6<<22)-(T7<<16);
    T_1[16]=A[7]*B[9]+A[8]*B[8]+A[9]*B[7];
    t16=T_1[16]+(T7<<22)-(T8<<16);
    T_1[17]=A[8]*B[9]+A[9]*B[8];
    t17=T_1[17]+(T8<<22)-(T9<<16);
    T_1[18]=A[9]*B[9];
    t18=T_1[18]+(T9<<22);
    T1_1=t10+(T9_1>>26);    //转折
    T[0]=T1_1&67108863;
    T2_1=t11+(T1_1>>26);
    T[1]=T2_1&67108863;
    T3_1=t12+(T2_1>>26);
    T[2]=T3_1&67108863;
    T4_1=t13+(T3_1>>26);
    T[3]=T4_1&67108863;
    T5_1=t14+(T4_1>>26);
    T[4]=T5_1&67108863;
    T6_1=t15+(T5_1>>26);
    T[5]=T6_1&67108863;
    T7_1=t16+(T6_1>>26);
    T[6]=T7_1&67108863;
    T8_1=t17+(T7_1>>26);
    T[7]=T8_1&67108863;
    T9_1=t18+(T8_1>>26);
    T[8]=T9_1&67108863;
    T[9]=T9_1>>26;

    *res = T;
}

// int main()
// {
//     unsigned long *res= NULL;
//     mont_mul_opt(&res);
//     printf("R=[");
//     for(int i=0;i<9;i++){
//         printf("%lu,",T[i]);
//     }
//     printf("%lu]\n",T[9]);
// }
