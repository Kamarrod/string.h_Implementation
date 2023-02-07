CFLAGS = -Wall -Werror -Wextra -std=c11
DOP_CFILES= s21_sprintf_d.c s21_sprintf_c.c parser.c s21_sprintf_u.c typecasting.c s21_sprintf_s.c s21_sprintf_f.c
DOP_OFILES= s21_sprintf_d.o s21_sprintf_c.o parser.o s21_sprintf_u.o typecasting.o s21_sprintf_s.o s21_sprintf_f.c
TEST_CFILES = test_sprintf_u.c test_sprintf_d.c test_sprintf_i.c test_sprintf_c.c test_sprintf_s.c test_sprintf_f.c test_sprintf_percent.c
TEST_OFILES = test_sprintf_u.o test_sprintf_d.o test_sprintf_i.o test_sprintf_c.o test_sprintf_s.o test_sprintf_f.o test_sprintf_percent.o  
TST_LIBS = $(shell pkg-config --libs check)
#TST_LIBS = -lcheck -lm -lpthread -lrt -lsubunit

all: test gcov_report
# s21_sprintf:
# 	gcc $(CFLAGS) s21_sprintf.c $(DOP_CFILES)
# 	gcc s21_sprintf.o $(DOP_OFILES) -o s21_sprintf.out
test:
	gcc $(CFLAGS) alltests.c s21_sprintf.c $(DOP_CFILES) $(TEST_CFILES) -lcheck -lpthread  -lm
	gcc alltests.o s21_sprintf.o $(DOP_OFILES) $(TEST_OFILES) -lcheck -lpthread  -lm  -o test.out
# alltests_valgrind:
# 	gcc -g alltests.c s21_sprintf.c $(DOP_CFILES) $(TEST_CFILES) -o alltests_valgrind.out -lcheck -lpthread -lm -D_GNU_SOURCE -lrt -lsubunit
gcov_report:
	gcc alltests.c s21_sprintf.c $(DOP_CFILES) $(TEST_CFILES) -o gcov_check.out $(TST_LIBS) --coverage
	./gcov_check.out
	lcov -t "s21_sprintf" -o s21_sprintf.info -c -d . 
	genhtml -o report s21_sprintf.info
	open ./report/index.html
clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf *.out
	rm -rf *.gcno
	rm -rf *.gcda
	rm -rf report
	rm -rf *.info
rebuild: clean all