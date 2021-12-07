#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

/*
输入：a,b； a、b可以都为64位，因为代码中mulq
输出：low(低64位)，high高(64位)
作用：得到a*b的结果

引用openssl代码，在openssl/crypto/bn/bn_lcl.h
*/
#define BN_UMULT_LOHI(low,high,a,b)  \
        asm ("mulq      %3"             \
                : "=a"(low),"=d"(high)  \
                : "a"(a),"g"(b)         \
                : "cc");

/*
输入：a,w
输出：结果r(64bit),进位值c(64bit)
得到a*b的结果r和进位值c(进位值c的位数范围是0-63bit)

引用openssl代码，在openssl/crypto/bn/bn_lcl.h
*/
#define mul(r,a,w,c)    {               \
        unsigned long high,low,ret,ta=(a);   \
        BN_UMULT_LOHI(low,high,w,ta);   \
        ret =  low + (c);               \
        (c) =  high;                    \
        (c) += (ret<low)?1:0;           \
        (r) =  ret;                     \
        }

//一个64bit的数能表示的最大10进制数，位数为19
#  define BN_DEC_CONV     (10000000000000000000UL)
#  define BN_DEC_NUM      19
//64位全1
#  define BN_MASK2        (0xffffffffffffffffL)

typedef struct{
   unsigned long *a;	/* Pointer to an array of 'BN_BITS2' bit */
   int last;	/* Index of last used d +1. */
   int max;	/* Size of the a array. */
}bignum;

bignum *bn_new(int digits);
int BN_add_word(bignum *a, unsigned long w);
int BN_mul_word(bignum *a, unsigned long w);
int dec2bn(bignum **bn, const char *a);
unsigned long bn_div_words(unsigned long h, unsigned long l, unsigned long d);
unsigned long BN_div_word(bignum *a, unsigned long w);
int BN_num_bits_word(unsigned long l);
int BN_num_bits(bignum *a);
bignum *BN_dup(const bignum *a);
int BN_is_zero(const bignum *a);
char *bn2dec(bignum *a);
int BN_add(bignum *r, bignum *a, bignum *b);
int BN_lshift64(bignum *a,int w);
bignum *BN_Zero(int digits);
bignum *BN_mul(bignum *a, bignum *b);