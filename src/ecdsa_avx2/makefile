UTILDIR=../../util/
app: mul_avx2.c $(UTILDIR)mm256op.c
	gcc -I$(UTILDIR) -mavx2 $^ -o $@