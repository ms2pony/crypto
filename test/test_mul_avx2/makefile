MUL_AVX2=/home/tam/crypto/src/ecdsa_avx2/mul_avx2.c
LibCrypto=/home/tam/crypto/openssl/libcrypto.a
test_mul_avx2: test_mul_avx2.c $(MUL_AVX2) $(LibCrypto)
	gcc -g -o $@ $^ -mavx2