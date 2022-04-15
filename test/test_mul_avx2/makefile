UTILDIR=../../util/
MUL_AVX2=/home/tam/crypto/src/ecdsa_avx2/mul_avx2.c
LibCrypto=/home/tam/crypto/openssl/libcrypto.a
app: test_mul_avx2.c $(MUL_AVX2) $(LibCrypto) $(UTILDIR)mm256op.c $(UTILDIR)show_mm256.c
	gcc -I$(UTILDIR) -g3 -o $@ $^ -mavx2