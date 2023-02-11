CFLAGS = -Wall -Werror -Wextra -c #-std=c11
#jeraldin
JER_CFILES= jer_sprintf_d.c jer_sprintf_c.c jer_parser.c jer_sprintf_u.c jer_typecasting.c jer_sprintf_s.c jer_sprintf_f.c jer_sprintf.c
JER_OFILES= jer_sprintf_d.o jer_sprintf_c.o jer_parser.o jer_sprintf_u.o jer_typecasting.o jer_sprintf_s.o jer_sprintf_f.o jer_sprintf.o
#arboktya
ARB_CFILES = arboktya.c
ARB_OFILES = arboktya.o
#camarrod
CAM_CFILES = camarrod.c
CAM_OFILES = camarrod.o

#common
TEST_CFILES = arb_tests.c jer_tests.c cam_tests.c
TEST_OFILES = arb_tests.o jer_tests.c cam_tests.o


TST_LIBS = $(shell pkg-config --libs check)
#TST_LIBS = -lcheck -lm -lpthread -lrt -lsubunit

all: test #gcov_report
test:
	gcc $(CFLAGS) alltests.c $(JER_CFILES) $(ARB_CFILES) $(CAM_CFILES) $(TEST_CFILES) -lcheck -lpthread  -lm
	gcc alltests.o $(JER_OFILES) $(ARB_OFILES) $(CAM_OFILES) $(TEST_OFILES) -lcheck -lpthread  -lm  -o alltests.out
gcov_report:
	gcc alltests.c $(CAM_CFILES) $(JER_CFILES) $(ARB_CFILES) $(TEST_CFILES) -o gcov_check.out $(TST_LIBS) --coverage
	./gcov_check.out
	lcov -t "gcheck" -o gcheck.info -c -d . 
	genhtml -o report gcheck.info
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