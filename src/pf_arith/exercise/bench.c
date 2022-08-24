#include <stdio.h>
void mont_mul_opt(unsigned long *res);

int main()
{
    unsigned long *res;
    long t1, t2, time = 0;
    for (int i = 0; i < 10000; i++)
    {
        asm volatile(
            "cpuid;rdtsc;mfence"
            : "=a"(t1) //一定要存，因为接下来肯定要用到eax
        );
        mont_mul_opt(res);
        asm volatile(
            "mfence;rdtsc;mfence"
            : "=a"(t2) //一定要存，因为接下来肯定要用到eax
        );
        time += t2 - t1;
    }
    printf("%ld\n", time / 10000);
    // printf("%d", res);
}