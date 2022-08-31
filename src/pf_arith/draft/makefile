CFLAGS=-O3 -march=native -mtune=native -mavx2
mont_mul=mul_avx2.o
CC=gcc

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

app: $(mont_mul) $(LIB) bench.c clock.c
	$(CC) $^ -o $@ -mavx2

clean:
	rm -rf a.out *.o app