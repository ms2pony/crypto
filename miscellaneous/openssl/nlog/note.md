## 未被编译的文件

crypto/bn/bn_asm.c 正常情况不会被编译，想要使用它，做法如下：
`gcc -I. -Icrypto/include -Iinclude -gdwarf-2 -g3 -c -o crypto/bn/bn_asm.o crypto/bn/bn_asm1.c`
