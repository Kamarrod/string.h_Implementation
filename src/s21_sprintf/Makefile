# Это комментарий, который говорит, что переменная CC указывает компилятор, используемый для сборки
CC=gcc
#Это еще один комментарий. Он поясняет, что в переменной CFLAGS лежат флаги, которые передаются компилятору
CFLAGS=-c -Wall -Wextra -Werror
OFILES= 
CFILES=
#TST_LIBS = $(shell pkg-config --libs check)
TST_LIBS = -lcheck -lm -lpthread -lrt -lsubunit
all: s21_sprintf test
s21_sprintf:
	$(CC) $(CFLAGS) s21_sprintf.c
	$(CC) s21_sprintf.o -o s21_sprintf
test:
# $(CC) $(CFLAGS) s21_string_test.c
# $(CC) s21_string_test.o $(TST_LIBS) -o s21_string_test.out
	gcc s21_string_test.c s21_sprintf.c -lcheck -lpthread  -lm  -o s21_string_test.out

clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf *.out
rebuild: clean all