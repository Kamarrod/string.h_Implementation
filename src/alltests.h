#ifndef ALLTESTS
#define ALLTESTS
#include <check.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>

#include "jer_sprintf.h"
#include "arboktya.h"
#include "camarrod.h"

#define BUFF_SIZE 512
//jeraldin
Suite *test_sprintf_unsigned(void);
Suite *test_sprintf_string(void);
Suite *test_sprintf_percent(void);
Suite *test_sprintf_signed_i(void);
Suite *test_sprintf_f(void);
Suite *test_sprintf_signed(void);
Suite *test_sprintf_c(void);
//arboktya
Suite* test_arboktya_string_funcs(void);
//camarrod
Suite* test_camarrod_string_funcs(void);
#endif  // ALLTESTS
