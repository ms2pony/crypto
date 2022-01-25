/* Construct a 256-bit vector from 4 64-bit doubles. Add it to itself
 * and print the result.
 */

#include <stdio.h>
#include <immintrin.h>

int main() {

  //double类型的30.0在内存中存储的数字可不是30啊！
  // __m256d a = _mm256_set_pd(30.0, 21.0, 31.0, 66.0); 

  //这个函数用于设置4个64位整数，__m256i代表一个向量，这个向量能存储32个字节
  
  __m256i a = _mm256_set_epi64x(20,30,40,50);

  // Does GCC generate the correct mov, or (better yet) elide the copy
  // and pass two of the same register into the add? Let's look at the assembly.
  __m256i b = _mm256_set_epi64x(60,80,90,100);


  // Add the two vectors, interpreting the bits as 4 double-precision
  // floats.
  __m256i c = _mm256_sub_epi64(b,a);

  // Do we ever touch DRAM or will these four be registers?
  __attribute__ ((aligned (32))) long long output1[4]={0,0,0,0};
  long long *output=(long long *)(&c);

  printf("%lld %lld %lld %lld\n",output[0], output[1], output[2], output[3]);
  return 0;
}
