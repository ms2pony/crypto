## 文件介绍

### bignum

文件夹，里面各种不同数据结构的bignum

#### avx2

数据结构为：用5个ymm寄存器存放两个256-bit的大数；limb大小为32-bit，64-bit的空间用来存放一个limb，
所以运算的过程中，limb的大小可以溢出

论文参考：Parallel Implementation of SM2 Elliptic Curve Cryptography on Intel Processors with AVX2

#### limb8

最普通的一种表示大数的形式，
其数据结构为：大端存放，limb为8-bit，可以使用openssl中的`BN_bin2bn`转换成openssl中的`BIGNUM`类型

### limb64

其数据结构为：大端存放，limb为64-bit，不能使用使用openssl中的`BN_bin2bn`转换成openssl中的`BIGNUM`类型，
与openssl中的`ecp_nistz256_mul_mont`函数兼容
