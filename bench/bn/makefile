CFLAG=-mavx2 -I$(OPENSSLINC) -I$(INCLUDEDIR)

INCLUDEDIR=/home/tam/github/crypto/include
OPENSSLINC=/home/tam/github/crypto/openssl/include
UTILDIR=/home/tam/github/crypto/util
MUL_AVX2=/home/tam/github/crypto/src/ecdsa_avx2/mul_avx2.c
LibCrypto=/home/tam/github/crypto/openssl/libcrypto.a
BN_AVX2=$(UTILDIR)/bn_avx2/bn_avx2_info.c $(UTILDIR)/bn_avx2/get_bn_avx2.c $(UTILDIR)/bn_avx2/show_bn_avx2.c
BN_CONVERT=$(UTILDIR)/bn_convert/bn_convert.c

OBJ=bn_avx2_info.o get_bn_avx2.o show_bn_avx2.o bn_convert.o mul_avx2.o

app1: bench_bn.cpp $(OBJ) $(LibCrypto)
	@# g++ -DMULAVX2 -I$(INCLUDEDIR) -g3 -o $@ $^ # linux shell下'#'开头的命令就相当于注释了，所以不执行
	g++ -DMULAVX2 -I$(INCLUDEDIR) \
	-O3 -o $@ $^ \
	# -O3的测量结果更小，编译器优化并不会破坏代码的测量功能

app2: bench_bn.cpp $(OBJ)
	g++ -L/home/tam/github/crypto/openssl -lcrypto -I$(INCLUDEDIR) -g3 -o $@ $^ # 动态链接的方式链接openssl库

bn_avx2_info.o: $(UTILDIR)/bn_avx2/bn_avx2_info.c
	gcc $(CFLAG) -c -o $@ $<

get_bn_avx2.o: $(UTILDIR)/bn_avx2/get_bn_avx2.c
	gcc $(CFLAG) -c -o $@ $<

show_bn_avx2.o: $(UTILDIR)/bn_avx2/show_bn_avx2.c
	gcc $(CFLAG) -c -o $@ $<

bn_convert.o: $(UTILDIR)/bn_convert/bn_convert.c
	gcc $(CFLAG) -c -o $@ $<

mul_avx2.o: $(MUL_AVX2)
	gcc -O3 -c -o $@ $< -mavx2

clean:
	@rm *.o app* -rf