## preliminary

### 参考资料缩写
说明：缩写便于引用
- Parallel Implementation of SM2 Elliptic Curve Cryptography on Intel Processors with AVX2 [PIOS2020]

### AVX2指令集
AVX2于2013年发布，AVX2是AVX的扩展，AVX只支持128-bit大整数指令，AVX2支持256-bit大整数指令。
主要指令如下：
1. VPMULUDQ
2. `_mm256_alignr_epi8`函数：
```fortran
FOR j := 0 to 1
	i := j*128
	tmp[255:0] := ((a[i+127:i] h<< 128)[255:0] OR b[i+127:i]) >> (imm8*8)
	dst[i+127:i] := tmp[127:0]
ENDFOR
dst[MAX:256] := 0
```

### 数据结构
这个部分讲的数据结构，在本文件中的大部分函数中都会用到

1. 大数的表示：使用5个256-bit的AVX2寄存器存放两个大数，

## 文件说明
说明：以下文件默认的位置为：src/ecdsa_avx2
1. mul_avx2.c: 讲了一些函数的实现(算法的实现过程)，相关数据结构，AVX2指令集相关知识
2. call_libcrypto.c 20年AVX2论文实现源代码
3. t3.py：
   验证AVX2论文实现源代码的运行结果
   - bigNum2Array 函数，大数转26bit数组(不限256bit大数)
   - array2BigNum 函数，26bit数组转大数(不限256bit大数)
4. Makefile：
   - t2 => t1.o 与 t2.o 链接，该target每次`make t2`都会执行(不管文件是否已经修改)
   - dll => 生成t2.so
   - time_test 这个target用于测试openssl1.1.1f的`ecp_nistz256_mul_mont`与20年AVX2论文并行实现的速度比较
   - all => 制作`dll`和`bin/app`；`bin/app`：链接`t1.c`与`t2.c`