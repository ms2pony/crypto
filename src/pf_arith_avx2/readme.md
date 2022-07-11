# title

目录名：AVX2_ECDSA 或 ecdsa_avx2

## 文件说明

- nlog：目录，有 log, note 等文件

- mul_avx2.c: 模乘运算，`PIOS2020`中的实现
- a.py：
  工具，用于辅助实现`PIOS2020`中的算法，有以下函数：
  - bigNum2Array 函数，大数转 26bit 数组(不限 256bit 大数)
  - array2BigNum 函数，26bit 数组转大数(不限 256bit 大数)

## 本地参考资料

主要是论文(pdf)，如下

- PIOS2020，论文缩写，mul_avx2.c 中代码的源于该论文中的算法，
  位置，`F:\iii\ii\i\paper\算法优化论文\密码算法优化\PIOS2020.pdf`
