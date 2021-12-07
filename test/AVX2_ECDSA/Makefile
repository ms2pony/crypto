CC=gcc -std=gnu11 -mavx2
# CFLAG=-O2
CFLAG=-g
CFLAG1=-O3 -g

.PHONY: all 
.PHONY: t2

all: bin/app dll

bin/app: t1.c t2.c
	$(CC) $(CFLAG) $^ -o $@

t2: t2.o t1.o
	gcc $(CFLAG) t1.c -c -o t1.o
	gcc $^ -o $@
t2.o: t2.c
	$(CC) $(CFLAG1) -c $< -o t2.o

dll: t2.so

%.so: %.c
	gcc -shared -mavx2 -fPIC $< -o $@

time_test: t2.o call_libcrypto.c
	gcc -mavx2 $^ -L/home/tam/Desktop/bignum/openssl -lcrypto -o $@


clean:
	rm bin/*