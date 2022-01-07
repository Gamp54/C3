CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: clean s21_cat

s21_cat: s21_cat.o
	gcc -g -std=c11 s21_cat.o -o s21_cat

s21_cat.o: s21_cat.c s21_cat.h
	$(CC) -c s21_cat.c

test:
	sh ../common/cat_test.sh

clean: 
	rm -f *.o s21_cat *.txt

rebuild: clean all
