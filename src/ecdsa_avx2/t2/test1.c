// #include <openssl/ec.h>
#include<x86intrin.h>
#include<stdio.h>
void __ecp_nistz256_mul_montx();



int main(){
	unsigned long t1=1,t2=1,time1,time2;

	unsigned long temp[4]={0};
	unsigned long temp1[4]={0};


	__asm__(
		"movq %0, %%rdi \n\t"
		"movq %1, %%rbx \n\t"
		: 
		: "r"(temp), "r"(temp1)
	);

	__ecp_nistz256_mul_montx();

	// __asm__ __volatile__ (
	// 	//rsi和rdi倍用做循环，不要用这两个寄存器
	// 	//ebx也不能用
	// 	"push %%rbp \n\t"
	// 	"movq $10000000, %%rsi \n\t"
	// 	"xorq %%rdi, %%rdi \n\t"
	// 	"rdtsc \n\t"
	// 	"shlq $0, %%rdx \n\t"
	// 	"orq %%rdx, %%rax \n\t"
	// 	"movq %%rax, %%rbx \n\t"
		
	// 	"							\
	// 	1:\tmulxq	%%r14,%%r9,%%r10; \
	// 	mulxq	%%r15,%%rcx,%%r11; \
	// 	xorl	%%eax,%%eax; \
	// 	adcq	%%rcx,%%r10; \
	// 	mulxq	%%r8,%%rbp,%%r12; \
	// 	movq	%%r14,%%rdx; \
	// 	adcq	%%rbp,%%r11; \
	// 	adcq	$0,%%r12; \
	// 	xorq	%%r13,%%r13; \
	// 	" //循环体

	// 	"incq %%rdi\n\t"
	// 	"cmpq %%rsi, %%rdi\n\t"
	// 	"jle 1b\n\t"
	// 	"rdtsc\n\t"
	// 	"shlq $0, %%rdx \n\t"
	// 	"orq %%rdx, %%rax \n\t"
	// 	"pop %%rbp\n\t"
	// 	// "movq %0, %%rdi \n\t"
	// 	// "movq %1, %%rbx \n\t"
	// 	// "movq %1, %%rbx \n\t"
	// 	: "=a"(t2), "=b"(t1)
	// 	: 
	// );

	

	// // t1=_rdtsc();
	// // for(int i=0;i<100000000;i++){
	// // 	t1+t2;
	// // }
	// // t2=_rdtsc();
	// time1=t2-t1;

	// __asm__ __volatile__ (
	// 	//rsi和rdi倍用做循环，不要用这两个寄存器
	// 	//ebx也不能用
	// 	"push %%rbp \n\t"
	// 	"movq $10000000, %%rsi \n\t"
	// 	"xorq %%rdi, %%rdi \n\t"
	// 	"rdtsc \n\t"
	// 	"shlq $0, %%rdx \n\t"
	// 	"orq %%rdx, %%rax \n\t"
	// 	"movq %%rax, %%rbx \n\t"
		
	// 	// "							\
	// 	// 1:\tmulxq	%%r14,%%r9,%%r10; \
	// 	// movq	%%r14,%%rdx; \
	// 	// adcq	%%rbp,%%r11; \
	// 	// mulxq	%%r15,%%rcx,%%r11; \
	// 	// xorl	%%eax,%%eax; \
	// 	// adcq	%%rcx,%%r10; \
	// 	// mulxq	%%r8,%%rbp,%%r12; \
	// 	// adcq	$0,%%r12; \
	// 	// xorq	%%r13,%%r13; \
	// 	// " //循环体

	// 	"							\
	// 	1:\tmulxq	%%r14,%%r9,%%r10; \
	// 	mulxq	%%r14,%%r9,%%rdx; \
	// 	mulxq	%%rbp,%%r9,%%r11; \
	// 	mulxq	%%r15,%%rcx,%%r11; \
	// 	mulxq	%%rax,%%rcx,%%rax; \
	// 	mulxq	%%rcx,%%rcx,%%r10; \
	// 	mulxq	%%r8,%%rbp,%%r12; \
	// 	adcq	$0,%%r12; \
	// 	mulxq	%%r13,%%r13,%%r13; \
	// 	" //循环体

	// 	"incq %%rdi\n\t"
	// 	"cmpq %%rsi, %%rdi\n\t"
	// 	"jle 1b\n\t"
	// 	"rdtsc\n\t"
	// 	"shlq $0, %%rdx \n\t"
	// 	"orq %%rdx, %%rax \n\t"
	// 	"pop %%rbp\n\t"
	// 	// "movq %0, %%rdi \n\t"
	// 	// "movq %1, %%rbx \n\t"
	// 	// "movq %1, %%rbx \n\t"
	// 	: "=a"(t2), "=b"(t1)
	// 	: 
	// );

	

	// t1=_rdtsc();
	// for(int i=0;i<100000000;i++){
	// 	t1+t2;
	// }
	// t2=_rdtsc();
	// time2=t2-t1;

	// printf("time1:\n%lu\n",time1);
	// printf("time2:\n%lu\n",time2);


}