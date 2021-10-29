#include<openssl/bn.h>
#include<openssl/bio.h>
#include<stdio.h>
#include<x86intrin.h>

char *str="abc127772942cabfffff2329382382397924792789abc";
char *stm="12c127732942cabfaaff2329382382397924792789abc";
char *std="6516516546546546516516565465456156165654";

// BN_ULONG bn_div_words1(BN_ULONG h, BN_ULONG l, BN_ULONG d);
BN_ULONG bn_div_words(BN_ULONG h, BN_ULONG l, BN_ULONG d);

int BN_num_bits_word(BN_ULONG l);


int main(){
	// char *str1="111111111111111111111111111111111111111111111";
	char *ctemp;
	char *ctemp1;
	unsigned long a1=1;
	unsigned long b1=787654654654;
	unsigned long c1=3487334;
	unsigned long w1=3487341331;
	char *str1;
	BIGNUM *a,*b,*r;
	a=BN_new();
	b=BN_new();
	r=BN_new();

	BN_hex2bn(&a,str);
	BN_hex2bn(&b,stm);
	BN_add(r,a,b);
	str1=BN_bn2hex(r);
	unsigned long temp=~3;
	BN_dec2bn(&r,std);
	temp = BN_num_bits(r);
	ctemp=BN_bn2dec(r);
	temp = (unsigned long)+1;

	// BIO_snprintf(ctemp1,4,"%lu",b1);
	sprintf(ctemp1,"%019lu",b1);

unsigned long t1,t2,time1,time2;

    // t1=_rdtsc();
    // for(int i=0;i<1000;i++){
    //     a1=bn_div_words1(c1,b1,w1);
    // }
    // t2=_rdtsc();
    // time1=t2-t1;

    // t1=_rdtsc();
    // for(int i=0;i<1000;i++){
    //     a1=bn_div_words(c1,b1,w1);
    // }
    // t2=_rdtsc();
    // time2=t2-t1;

	BN_num_bits_word(b1);

}
