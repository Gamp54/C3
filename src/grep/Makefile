CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: clean s21_grep

s21_grep: s21_grep.o
	gcc -g -std=c11 -$CFLAGS -lpcre s21_grep.o -o s21_grep

s21_grep.o: s21_grep.c s21_grep.h
	$(CC) -c s21_grep.c

test:
	sh ../common/grep_test.sh

clean: 
	rm -f *.o s21_grep *.txt

rebuild: clean all
