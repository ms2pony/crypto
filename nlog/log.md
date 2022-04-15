## 进展

20211101 更新，最新进展，问题应该出在`BN_add`函数

`BN_mul`函数总是算不出正确结果

通过下面的调试发现了`BN_num_bits`函数有问题
执行了`410 BN_add(ret,ret,t[i]);`这个代码后，使用如下命令查看：
(gdb) p bn2dec(ret)
$18 = 0x55555555adf0 "0032256867042516975857604552528249241930509184199477558762"
发现高位两个 0，这表明`BN_num_bits`函数有问题

自己实现大整数库；还有一个 openssl 仓库可以对它进行测试

# 下载 openssl 仓库

git clone <https://github.com/openssl/openssl.git>

## 有问题的分支，`./config`执行时会出错，OpenSSL_1_1_0g 等分支会有问题

## 切换到合适分支

git checkout -b 1.1.0stable origin/OpenSSL_1_1_0-stable

## 某些分支名会出现前面有`head`的问题，解决方法如下

git branch -m OpenSSL_1_1_0f openssl-1.1.0f # 改分支名，避免混淆

## 修改 makefile 中的 cflag，此处省略

# `openssl`仓库

## 未被编译的文件

crypto/bn/bn_asm.c 正常情况不会被编译，想要使用它，做法如下：
`gcc -I. -Icrypto/include -Iinclude -gdwarf-2 -g3 -c -o crypto/bn/bn_asm.o crypto/bn/bn_asm1.c`

# `bignum`目录下

通过修改`makfile`来控制不同的代码编译 1.`t1.c`用于测试 openssl 仓库的代码：
`gcc -o app t1.o /home/tam/Desktop/bignum/openssl/libcrypto.a test/bn_asm.o -ldl -pthread` 2.`basic.c`是自己的大整数代码
