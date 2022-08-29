#include <stdio.h>
#include "clock.h"
void mont_mul_opt(unsigned long **res);
unsigned long* mul(unsigned long A[10],unsigned long B[10]);

extern unsigned long A[10],B[10];

int main()
{
    const int BENCH = 800;
    unsigned long *res;

    // CLOCKS(MontMul,mont_mul_opt(&res));
    CLOCKS(MontMul,mul(A,B));

}