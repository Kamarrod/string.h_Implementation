# Это комментарий, который говорит, что переменная CC указывает компилятор, используемый для сборки
CC=gcc
#Это еще один комментарий. Он поясняет, что в переменной CFLAGS лежат флаги, которые передаются компилятору
CFLAGS=-c #-Wall -Wextra -Werror
DOP_CFILES= s21_sprintf_d.c s21_sprintf_c.c parser.c s21_sprintf_u.c typecasting.c
DOP_OFILES= s21_sprintf_d.o s21_sprintf_c.o parser.o s21_sprintf_c.o typecasting.o
#TST_LIBS = $(shell pkg-config --libs check)
TST_LIBS = -lcheck -lm -lpthread -lrt -lsubunit
all: s21_sprintf
s21_sprintf:
#$(CC) $(CFLAGS) s21_sprintf.c $(DOP_CFILES)
#$(CC) s21_sprintf.o $(DOP_OFILES) -o s21_sprintf.out
	gcc -g s21_sprintf.c $(DOP_CFILES) -o s21_sprintf.out
testd:
	gcc test_sprintf_d.c s21_sprintf.c $(DOP_CFILES) -lcheck -lpthread  -lm  -o test_d.out
testi:
	gcc test_sprintf_i.c s21_sprintf.c $(DOP_CFILES) -lcheck -lpthread  -lm  -o test_i.out
testc:
	gcc test_sprintf_c.c s21_sprintf.c $(DOP_CFILES) -lcheck -lpthread  -lm  -o test_c.out
testu:
	gcc test_sprintf_u.c s21_sprintf.c $(DOP_CFILES) -lcheck -lpthread  -lm  -o test_u.out

clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf *.out
rebuild: clean all