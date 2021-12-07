# 文件说明
1. AVX2_ECDSA/t2.c 20年AVX2论文实现源代码
2. AVX2_ECDSA/call_libcrypto.c 20年AVX2论文实现源代码
3. AVX2_ECDSA/t3.py：
   验证AVX2论文实现源代码的运行结果
   - bigNum2Array 函数，大数转26bit数组(不限256bit大数)
   - array2BigNum 函数，26bit数组转大数(不限256bit大数)
4. AVX2_ECDSA/Makefile：
   - t2 => t1.o 与 t2.o 链接，该target每次`make t2`都会执行(不管文件是否已经修改)
   - dll => 生成t2.so
   - time_test 这个target用于测试openssl1.1.1f的`ecp_nistz256_mul_mont`与20年AVX2论文并行实现的速度比较
   - all => 制作`dll`和`bin/app`；`bin/app`：链接`t1.c`与`t2.c`

# avx2内联函数
