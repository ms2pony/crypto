CFLAGS=-I/home/tam/github/crypto/external/openssl -g -w
LIB=/home/tam/github/crypto/external/openssl/libcrypto.a
mont_mul=mont_mul.o
CC=clang

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

app: $(mont_mul) $(LIB)
	$(CC) $^ -o $@

clean:
	rm -rf a.out *.o app