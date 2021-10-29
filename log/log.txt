# `openssl`目录下
gcc -I. -Icrypto/include -Iinclude -gdwarf-2 -g3 -c -o crypto/bn/bn_asm.o crypto/bn/bn_asm1.c

# `bignum`目录下
gcc -o app t1.o /home/tam/Desktop/bignum/openssl/libcrypto.a test/bn_asm.o -ldl -pthread