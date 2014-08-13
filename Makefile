CC=gcc
CFLAGS=-std=c99
OBJS=String.o Array.o Dictionary.o Buffer.o
HEADERS=String.h Array.h Dictionary.h Buffer.h

all: libcute.a test words

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<
libcute.a: $(OBJS) 
	ar rcs libcute.a $(OBJS)
test: test.o libcute.a $(HEADERS)
	gcc -L. -o test test.o -lcute
words: words.o libcute.a $(HEADERS)
	gcc -L. -o words words.o -lcute 
clean:
	rm $(OBJS)
	rm libcute.a
	rm test words
	
