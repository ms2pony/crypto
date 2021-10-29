CFLAGS=-gdwarf-2 -g3
CC=gcc

TARGET=app
SRCS=basic.c

OBJS=$(SRCS:.c=.o)

INC=-I$(shell echo ~)/Desktop/bignum/openssl/include

LIB=$(shell echo ~)/Desktop/bignum/openssl/libcrypto.a

SLIB=-ldl -pthread

# $(TARGET):$(OBJS)
# 	@echo TARGET:$@
# 	@echo OBJECTS:$^
# 	$(CC) -o $@ $^ $(LIB) $(SLIB)

# basic专用
$(TARGET):$(OBJS)
	@echo TARGET:$@
	@echo OBJECTS:$^
	$(CC) -o $@ $^


clean:
	rm -rf $(TARGET) $(OBJS)