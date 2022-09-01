CFLAGS=-O3 -march=native -mtune=native -mavx2
mont_mul=mont_mul_opt.o
mont_mul2=/home/tam/github/crypto/src/pf_arith_avx2/mul_avx2.o
CC=clang

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

app: $(mont_mul) bench.c clock.c
	$(CC) $^ -o $@

app2: $(mont_mul2) bench.c clock.c
	$(CC) $^ -o $@ -mavx2

clean:
	rm -rf a.out *.o app