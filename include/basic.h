#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

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