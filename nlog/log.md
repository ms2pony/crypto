## 20220701

### 增加一个实验-==todo==

`/home/tam/github/crypto/bench/bn/bench_bn.cpp`的代码需要额外分离成一个实验

## 20211101

20211101 更新，最新进展，问题应该出在`BN_add`函数

### `BN_mul`函数总是算不出正确结果

通过下面的调试发现了`BN_num_bits`函数有问题
执行了`410 BN_add(ret,ret,t[i]);`这个代码后，使用如下命令查看：
(gdb) p bn2dec(ret)
$18 = 0x55555555adf0 "0032256867042516975857604552528249241930509184199477558762"
发现高位两个 0，这表明`BN_num_bits`函数有问题

### `BN_add`函数有问题

`BN_add`函数有问题，两个数相加就得判断一次进位，所以三个数相加不止要判断一次，另外使用内联汇编实现会比c语言要容易
