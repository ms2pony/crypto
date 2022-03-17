# intel avx2 内联函数对应功能的python函数

a=[26,27,28,29]
b = [36, 37, 38, 39]


def _mm256_alignr_epi8(a:int, b:int, imm8:int):
    j=0
    while(j<2):
        i=j*128
        tmp=a[i+127:i]<<128

        j+=1
