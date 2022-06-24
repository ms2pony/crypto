INCLUDEDIR=../../include
UTILDIR=/home/tam/github/crypto/util
MUL_AVX2=/home/tam/github/crypto/src/ecdsa_avx2/mul_avx2.c
LibCrypto=/home/tam/github/crypto/openssl/libcrypto.a
BN_AVX2=$(UTILDIR)/bn_avx2/bn_avx2_info.c $(UTILDIR)/bn_avx2/get_bn_avx2.c $(UTILDIR)/bn_avx2/show_bn_avx2.c
BN_CONVERT=$(UTILDIR)/bn_convert/bn_convert.c
app: test_mul_avx2.c $(MUL_AVX2) $(LibCrypto) $(BN_AVX2) $(BN_CONVERT)
	gcc -I$(INCLUDEDIR) -g3 -o $@ $^ -mavx2