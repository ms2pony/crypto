#include <immintrin.h>
#include<x86intrin.h>
#include<stdio.h>

__m256i A_B[5];
__m256i C_D[5];
__m256i* computer_256(__m256i A_B[5], __m256i C_D[5]);
void test1(__m256i A_B[5],__m256i C_D[5]);
void test2(__m256i A_B[5],__m256i C_D[5]);
void test3(__m256i A_B[5],__m256i C_D[5]);



int main(){
	A_B[0] = _mm256_set_epi64x(561654,34134,3454,542542);
	A_B[1] = _mm256_set_epi64x(452542,305623,40823,5015684);
	A_B[2] = _mm256_set_epi64x(4524545,3550,416450,55160);
	A_B[3] = _mm256_set_epi64x(42452,30551,40515,50231);
	A_B[4] = _mm256_set_epi64x(42492,30581,405195,502391);

	C_D[0] = _mm256_set_epi64x(24254,344134,34554,542542);
	C_D[1] = _mm256_set_epi64x(25454,344134,38454,542542);
	C_D[2] = _mm256_set_epi64x(24254,341354,348754,542542);
	C_D[3] = _mm256_set_epi64x(24454,341934,34854,542542);
	C_D[4] = _mm256_set_epi64x(24574,3417834,34854,542542);


	unsigned long t1,t2,time1,time2,time3;

	t1=_rdtsc();
	for(int i=0;i<10000000;i++){
		test3(A_B,C_D);
	}
	t2=_rdtsc();

	time3=t2-t1;

	for(int i=0;i<1000;i++){
		test1(A_B,C_D);
	}

	t1=_rdtsc();
	for(int i=0;i<10000000;i++){
		test1(A_B,C_D);
	}
	t2=_rdtsc();
	time1=t2-t1;

	for(int i=0;i<100000;i++){
		test2(A_B,C_D);
	}
	t1=_rdtsc();
	for(int i=0;i<10000000;i++){
		test2(A_B,C_D);
	}
	t2=_rdtsc();

	time2=t2-t1;

	

	printf("time1:\n%lu\n",time1);
	printf("time2:\n%lu\n",time2);
	printf("time3:\n%lu\n",time3);


	


}