# Luke Jiang
# CSE 374 HW 5
# May 8 2018

# This is the Makefile file used for compiling HW5 project.

CC = gcc
CFLAGS = -Wall -std=c11 -g

t9: trie.o t9.o
	$(CC) $(CFLAGS) -o t9 trie.o t9.o

trie.o: trie.h trie.c
	$(CC) $(CFLAGS) -c trie.h trie.c

t9.o: t9.c trie.h
	$(CC) $(CFLAGS) -c trie.h t9.c

clean:
	rm t9 *.o *~
