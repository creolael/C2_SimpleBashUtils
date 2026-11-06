CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

all: s21_cat

s21_cat: s21_cat.o
	$(CC) $(CFLAGS) s21_cat.o -o s21_cat

s21_cat.o: s21_cat.c s21_cat.h
	$(CC) $(CFLAGS) -c s21_cat.c

clean: 
	rm -f *.o s21_cat

re: clean all

.PHONY: all clean re

