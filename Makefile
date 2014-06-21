CC=gcc
CFLAGS=-std=c99
OBJS=String.o Array.o Dictionary.o
HEADERS=String.h Array.h Dictionary.h

all: libcute.a test

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<
libcute.a: $(OBJS) 
	ar rcs libcute.a $(OBJS)
test: test.o libcute.a $(HEADERS)
	gcc -L. -o test test.o -lcute -lm
clean:
	rm $(OBJS)
	rm libcute.a
	rm test
	
