## 背景

### 1 shell 中的变量和程序中变量的联系

[AES 学习-github 仓库](https://github.com/matt-wu/AES/)中提到：
openssl 中 AES 性能测试的方法：

> 关闭硬件加速 1/2/4/8 线程 AES-256/128-CBC：
> `OPENSSL_ia32cap="~0x200000200000000" openssl speed -multi {1/2/4/8} -elapsed -evp {aes-256/128-cbc}`
>
> 开启硬件加速 1/2/4/8 线程 AES-256/128-CBC：
> `openssl speed -multi {1/2/4/8} -elapsed -evp {aes-256/128-cbc}`
>
> 超线程的开户与关闭只能通过 UEFI/BIOS 来设置，测试命令同上。

其中第一行的测试命令的设置`OPENSSL_ia32cap`变量，需要和后面的`openssl speed`一起执行，分别执行就无法关闭硬件加速

<mark>所以写在一起是不是就是说`OPENSSL_ia32cap`此时不是个环境变量，而是程序中的变量</mark>

### 2 难以寻找`OPENSSL_ia32cap`在 openssl 中的定义

在阅读 openssl 项目代码时，发现个地方使用了变量`OPENSSL_ia32cap`，但是很难找到这个变量的定义。

## 探究`OPENSSL_ia32cap`变量

与该变量相关的东西有:

- `OPENSSL_cpuid_setup`函数，`OPENSSL_ia32_cpuid`函数
- `x86_64cpuid.s`文件(由`openssl/crypto/x86_64cpuid.pl`生成)，`openssl/crypto/cpuid.c`文件
- 涉及的代码：

  - `openssl/crypto/cpuid.c`中：

  ```c
  OPENSSL_ia32cap_P[0] = (unsigned int)vec | (1 << 10);
  OPENSSL_ia32cap_P[1] = (unsigned int)(vec >> 32);
  ```

  - `crypto/x86_64cpuid.s:178`：

  ```asm
  movl    %ecx,12(%rdi)
  ```

### 定义的位置

`openssl/crypto/cpuid.c`中，有两处：

```c
unsigned int OPENSSL_ia32cap_P[4]; // line159
# if defined(OPENSSL_CPUID_OBJ)
//...
# else
extern unsigned int OPENSSL_ia32cap_P[4]; //line17
# endif
```

分析上面的 c 代码，看起来好像一个文件中定义了两个，但其实生成的 makefile 中的 gcc 添加了一个选项`-DOPENSSL_CPUID_OBJ`，使得`# else`后的代码不会执行

### 对 OPENSSL_ia32cap_P 的赋值过程

该变量是个数组，有 4 个元素，但只有前 3 个元素会被赋值，赋值的代码如下：

```asm
# crypto/x86_64cpuid.s:178
movl    %ecx,12(%rdi) # 赋值OPENSSL_ia32cap_P[2]
```

```c
# openssl/crypto/cpuid.c
OPENSSL_ia32cap_P[0] = (unsigned int)vec | (1 << 10);
OPENSSL_ia32cap_P[1] = (unsigned int)(vec >> 32);
```

## 参考资料

[AES 学习-github 仓库](https://github.com/matt-wu/AES/)
