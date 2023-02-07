// #include <check.h>
// #include <stdio.h>
// #include <string.h>
// #include <locale.h>
// #include "s21_sprintf.h"
// #include <limits.h>
// #define BUFF_SIZE 512
#include "alltests.h"
START_TEST(sprintf_1_percent) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "%%Test %d Test";
  int val = 10;
  ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2_percent) {
  char str1[100];
  char str2[100];
  char *str3 = "Test %d Tes%%%%t %d";
  int val = 11;
  int val2 = 111;
  ck_assert_int_eq(sprintf(str1, str3, val, val2),
                   s21_sprintf(str2, str3, val, val2));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3_percent) {
  char str1[100];
  char str2[100];
  char *str3 = "%d Te%%st %d Test %d";
  int val = 3015;
  int val2 = 712;
  int val3 = 99;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

Suite *test_sprintf_percent(void) {
  Suite *s = suite_create("\033[45m-=S21_SPRINTF_PERCENT=-\033[0m");
  TCase *tc = tcase_create("sprintf_tc");

  tcase_add_test(tc, sprintf_1_percent);
  tcase_add_test(tc, sprintf_2_percent);
  tcase_add_test(tc, sprintf_3_percent);

  suite_add_tcase(s, tc);
  return s;
}

// int main(void) {
//     setlocale(LC_ALL, "");
//     int nf;
//     Suite *s1;
//     SRunner *sr;
//     s1 = test_sprintf_percent();
//     sr = srunner_create(s1);

//     //srunner_run_all(sr, CK_ENV);
//     //srunner_run_all(sr, CK_NORMAL);
//     srunner_set_fork_status(sr, CK_NOFORK);
//     srunner_run_all(sr, CK_VERBOSE);

//     nf = srunner_ntests_failed(sr);
//     //srunner_free(sr);
//     return nf == 0 ? 0 : 1;
// }
