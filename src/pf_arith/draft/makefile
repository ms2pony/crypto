CFLAGS=-I/home/tam/github/crypto/external/openssl -O3
LIB=/home/tam/github/crypto/external/openssl/libcrypto.a
mont_mul=t1.s
CC=clang

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

# app: $(mont_mul) $(LIB)
# 	$(CC) $^ -o $@

app: $(mont_mul) $(LIB) bench.c clock.c
	$(CC) $^ -o $@

clean:
	rm -rf a.out *.o app