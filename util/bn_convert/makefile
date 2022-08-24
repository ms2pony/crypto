UTILDIR=../../include
BN_AVX2=../bn_avx2/bn_avx2_info.c ../bn_avx2/get_bn_avx2.c ../bn_avx2/show_bn_avx2.c
LibCrypto=/home/tam/github/crypto/openssl/libcrypto.a
app: $(BN_AVX2) bn_convert.c $(LibCrypto)
	gcc -I$(UTILDIR) -g3 -o $@ $^ -mavx2

clean:
	rm ./app