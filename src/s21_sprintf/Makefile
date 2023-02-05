# Это комментарий, который говорит, что переменная CC указывает компилятор, используемый для сборки
CC=gcc
#Это еще один комментарий. Он поясняет, что в переменной CFLAGS лежат флаги, которые передаются компилятору
CFLAGS=-c #-Wall -Wextra -Werror
DOP_CFILES= s21_sprintf_d.c s21_sprintf_c.c parser.c s21_sprintf_u.c typecasting.c s21_sprintf_s.c s21_sprintf_f.c
DOP_OFILES= s21_sprintf_d.o s21_sprintf_c.o parser.o s21_sprintf_c.o typecasting.o s21_sprintf_s.o s21_sprintf_f.c
TEST_CFILES = test_sprintf_u.c test_sprintf_d.c test_sprintf_i.c test_sprintf_c.c test_sprintf_s.c test_sprintf_f.c test_sprintf_percent.c 
#TST_LIBS = $(shell pkg-config --libs check)
TST_LIBS = -lcheck -lm -lpthread -lrt -lsubunit
all: s21_sprintf
s21_sprintf:
#$(CC) $(CFLAGS) s21_sprintf.c $(DOP_CFILES)
#$(CC) s21_sprintf.o $(DOP_OFILES) -o s21_sprintf.out
	gcc -g s21_sprintf.c $(DOP_CFILES) -o s21_sprintf.out
alltests:
	gcc alltests.c s21_sprintf.c $(DOP_CFILES) $(TEST_CFILES) -lcheck -lpthread  -lm  -o alltests.out
alltests_valgrind:
	gcc -g alltests.c s21_sprintf.c $(DOP_CFILES) $(TEST_CFILES) -o alltests_valgrind.out -lcheck -lpthread -lm -D_GNU_SOURCE -lrt -lsubunit
clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf *.out
rebuild: clean all