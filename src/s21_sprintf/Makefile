# Это комментарий, который говорит, что переменная CC указывает компилятор, используемый для сборки
CC=gcc
#Это еще один комментарий. Он поясняет, что в переменной CFLAGS лежат флаги, которые передаются компилятору
CFLAGS=-c #-Wall -Wextra -Werror
DOP_CFILES= s21_sprintf_d.c s21_sprintf_c.c parser.c s21_sprintf_u.c typecasting.c s21_sprintf_s.c s21_sprintf_f.c
DOP_OFILES= s21_sprintf_d.o s21_sprintf_c.o parser.o s21_sprintf_c.o typecasting.o s21_sprintf_s.o s21_sprintf_f.c
#TST_LIBS = $(shell pkg-config --libs check)
TST_LIBS = -lcheck -lm -lpthread -lrt -lsubunit
all: s21_sprintf
s21_sprintf:
#$(CC) $(CFLAGS) s21_sprintf.c $(DOP_CFILES)
#$(CC) s21_sprintf.o $(DOP_OFILES) -o s21_sprintf.out
	gcc -g s21_sprintf.c $(DOP_CFILES) -o s21_sprintf.out
test_d:
	gcc test_sprintf_d.c s21_sprintf.c $(DOP_CFILES) -lcheck -lpthread  -lm  -o test_d.out
test_i:
	gcc test_sprintf_i.c s21_sprintf.c $(DOP_CFILES) -lcheck -lpthread  -lm  -o test_i.out
test_c:
	gcc test_sprintf_c.c s21_sprintf.c $(DOP_CFILES) -lcheck -lpthread  -lm  -o test_c.out
test_u:
	gcc test_sprintf_u.c s21_sprintf.c $(DOP_CFILES) -lcheck -lpthread  -lm  -o test_u.out
test_s:
	gcc test_sprintf_s.c s21_sprintf.c $(DOP_CFILES) -lcheck -lpthread  -lm  -o test_s.out
test_f:
	gcc test_sprintf_f.c s21_sprintf.c $(DOP_CFILES) -lcheck -lpthread  -lm  -o test_f.out

clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf *.out
rebuild: clean all