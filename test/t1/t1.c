#include <x86intrin.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    long t1 = _rdtsc();
    sleep(3);
    long t2 = _rdtsc();

    printf("%llu\n", t2 - t1);
    return 0;
}