CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

all: s21_grep

s21_grep: s21_grep.o
	$(CC) $(CFLAGS) s21_grep.o -o s21_grep

s21_grep.o: s21_grep.c s21_grep.h
	$(CC) $(CFLAGS) -c s21_grep.c

clean:
	rm -f *.o s21_grep

re: clean all

.PHONY: all clean re