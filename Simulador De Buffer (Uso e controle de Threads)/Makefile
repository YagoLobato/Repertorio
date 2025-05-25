CC = gcc
CFLAGS = -Wall -g -pthread

all: buffer_simples A B C

buffer_simples: buffer_simples.c
	$(CC) $(CFLAGS) buffer_simples.c -o buffer_simples

A: A.c
	$(CC) $(CFLAGS) A.c -o A

B: B.c
	$(CC) $(CFLAGS) B.c -o B

C: C.c
	$(CC) $(CFLAGS) C.c -o C
clean:
	rm -f buffer_simples A B C

