/**
 * @file eg1.c
 *
 * @brief mm256的基本使用，compile use：gcc eg1.c -mavx2
 *
 * @version 0.1
 * @date 2022-03-13
 * @author pony (mspony@163.com)
 * @require
 */

#include <stdio.h>
// #include <immintrin.h>
#include <x86intrin.h> //包含了immintrin.h
#include <stdint.h>

void learn_m256i()
{
  // 这个函数用于设置4个64位整数，__m256i代表一个向量，这个向量能存储32个字节
  __m256i a = _mm256_set_epi64x(20, 30, 40, 50);
  // printf输出50 40 30 20，可见a=_mm256_set_epi64x(20, 30, 40, 50)
  // 与__m256i a={50,40,30,20}的赋值方向是反的
  // __m256i变量可以当做数组名
  printf("a is:\t%lld %lld %lld %lld\n", a[0], a[1], a[2], a[3]);

  __m256i b = _mm256_set_epi64x(60, 80, 90, 100);
  __m256i c = _mm256_sub_epi64(b, a); //向量减法b-a

  //类型转换
  // `typedef __attribute((vector_size(32))) long long __m256i` 中的32指该向量类型__m256i大小为32字节
  long long *output = (long long *)(&c);
  printf("output is:\t%lld %lld %lld %lld\n", output[0], output[1], output[2], output[3]);
}

void m256ito32()
{
  __m256i A = _mm256_set_epi32(1, 2, 3, 4, 5, 6, 7, 8);

  // __m256i类型的A的A[i]是64bit的
  // 所以输出的不是8,7,6,5
  printf("A:\n");
  for (int i = 0; i < 4; i++)
  {
    printf("%lld\t", A[i]);
  }
  printf("\n");

  // 为了输出32bit的元素，需要做类型转换
  int32_t *A_32 = (int32_t *)(&A);
  printf("A_32:\n");
  for (int i = 0; i < 8; i++)
  {
    printf("%d\t", A_32[i]);
  }
  printf("\n");
}

void learn_m256d()
{
  // double类型的30.0在内存中存储的数据可不是30啊！
  __m256d a = _mm256_set_pd(30.0, 21.0, 31.0, 66.0);
}

int main()
{
  learn_m256i();
  m256ito32();
  learn_m256d();

  return 0;
}
