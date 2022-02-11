t2.o: t2.c
	gcc -g -O3 -c $@ $< -mavx2

app: t2.o t1.c
	gcc 