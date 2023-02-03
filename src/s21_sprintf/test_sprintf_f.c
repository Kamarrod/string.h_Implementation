#include <check.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "s21_sprintf.h"
#include <limits.h>
#define BUFF_SIZE 512

START_TEST(sprintf_1_f) {
  char str1[200];
  char str2[200];
  char *str3 = "%f TEST %.f TEST %4f TEST %4.f TEST %5.10f!";
  double num = 76.756589367;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2_f) {
  char str1[200];
  char str2[200];
  char *str3 = "%f TEST %.f TEST %3f TEST %4.f TEST %5.10f!";
  double num = -76.756589367;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3_f) {
  char str1[400];
  char str2[400];
  char *str3 = "%Lf\n%.Lf!";
  long double num_long = -76.756589;
  ck_assert_int_eq(sprintf(str1, str3, num_long, num_long),
                   s21_sprintf(str2, str3, num_long, num_long));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_4_f) {
  char str1[400];
  char str2[400];
  char *str3 = "%20.10f\n%20.15f\n%-20.5f!";
  double num = -76.756589;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_5_f) {
  char str1[400];
  char str2[400];
  char *str3 = "%Lf\n%.Lf\n%+-#Lf\n%+#.Lf\n%-#.Lf!";
  long double num = 76.756589;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_6_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %5f\ntest: %6.1f\ntest: %8.2f!";
  double num = 76.756589;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_7_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %10.5f\ntest: %12.4f!";
  double num = 76.756589;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_8_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %15.1f\ntest: %16.2f\ntest: %18.3f!";
  double num = -7648938790.756589;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_9_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %10.4f\ntest: %25.5f!";
  double num = -7648938790.756589;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_10_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %+15.f\ntest: %+#16.f\ntest: %+#18.0f!";
  double num = 7648938790.756589;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_11_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %+ 18.0f\ntest: %+10.f\ntest: %+25.f!";
  double num = 7648938790.756589;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_12_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %-26.1f\ntest: %-18.0f\ntest: %#-10.f!";
  double num = 7648938790.756589;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_13_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %-#15.f\ntest: %-+25.f!";
  double num = 7648938790.756589;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_14_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %-15.4f!\ntest: %-26.1f!\ntest: %-18.0f!";
  double num = -365289.3462865487;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_15_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %#-10.9f!\ntest: %-+25.15f!";
  double num = -365289.3462865487;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_16_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %15.13f!\ntest: %26.15f!";
  double num = -365289.34628654873789362746834;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_17_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %18.7f!\ntest: %10.15f!\ntest: %25.15f!";
  double num = -365289.34628654873789362746834;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_18_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %15.13f!\ntest: %26.15f!";
  double num = 365289.34628654873789362746834;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_19_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %18.7f!\ntest: %10.15f!";
  double num = 365289.34628654873789362746834;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_20_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %- 23.14f!\ntest: %+ 25.15f!";
  double num = 365289.34628654873789362746834;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_21_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: % 15f!\ntest: % -26f!\ntest: %- 18f!";
  double num = -365789.34;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_22_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %+- 14f!\ntest: %+ 10f!\ntest: % +25f!";
  double num = -365789.34;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_23_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: % 14f!\ntest: % -27f!\ntest: %- 19f!";
  double num = 365789.34;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_24_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %+- 16f!\ntest: %+ 44f!\ntest: % +35f!";
  double num = 365789.34;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_25_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %26Lf!\ntest: %18Lf!\ntest: %60Lf!";
  long double num = -3752765839673496.34;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_26_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %15Lf!test: %100Lf!";
  long double num = -3752765839673496.34;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_27_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %- 26Lf!\ntest: %+- 18Lf!\ntest: %60Lf!";
  long double num = 3752765839673496.34;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_28_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: % +15Lf!test: %100Lf!";
  long double num = 3752765839673496.34;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_30_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %020f!\ntest: %-020f!\ntest: %+025f!";
  double num = 837564.4753366;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_31_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %-+ 025.5f!\ntest: %- 020.4f\ntest: %+ 016.6f!";
  double num = 837564.4753366;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_32_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %015f!\ntest: %-026f!\ntest: %+018f!";
  double num = -947.6785643;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_33_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %+- 010.2f!\ntest: %- 025.7f\ntest: %+- 18.4f!";
  double num = -947.6785643;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_34_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: % 15.1Lf!\ntest: % -26.15Lf!\ntest: %- 30.15Lf!";
  long double num = 278.723786;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_35_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %+ 50.15Lf!\ntest: % +40.15Lf!";
  long double num = 278.723786;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_36_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: % 15.1Lf!\ntest: % -26.13Lf!\ntest: %- 30.8Lf!";
  long double num = -2358.367776967;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_37_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %+ 50.14Lf!\ntest: % +40.14Lf!";
  long double num = -2358.367776967;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_38_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %.1Lf!\ntest: %.2Lf!\ntest: %.3Lf!";
  long double num = -9999.99999;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_39_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %.10Lf!\ntest: %.6Lf!\ntest: %.Lf!";
  long double num = -9999.99999;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_40_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %.1Lf!\ntest: %.2Lf!\ntest: %.3Lf!";
  long double num = 000000000000000.00000000000;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_41_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %.6Lf!\ntest: %.Lf\ntest: %+ 0Lf!!";
  long double num = 000000000000000.00000000000;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_42_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %.1Lf!\ntest: %.2Lf!\ntest: %.3Lf!";
  long double num = -635293201236310753.6495633;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_43_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %+ 0Lf!\ntest: %.6Lf!\ntest: %.15Lf!";
  long double num = -635293201236310753.6495633;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_44_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %.1Lf!\ntest: %.2Lf!\ntest: %.3Lf!";
  long double num = -236310753.6495633;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_45_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %+ 0Lf!\ntest: %.6Lf!\ntest: %.15Lf!";
  long double num = -236310753.6495633;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_46_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %.1Lf!\ntest: %.2Lf!\ntest: %.3Lf!";
  long double num = -9325781235683689988.;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_47_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %+ 0Lf!\ntest: %.6Lf!\ntest: %.15Lf!";
  long double num = -9325781235683689988.;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_48_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %.1Lf!\ntest: %.2Lf!\ntest: %.3Lf!";
  long double num = 823631075973858585858447757573.6495633;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_49_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %+ 0Lf!\ntest: %.6Lf!\ntest: %.15Lf!";
  long double num = 823631075973858585858447757573.6495633;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_50_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %25.5Lf!\ntest: %Lf!\ntest: %-50Lf!";
  long double num = -9325781235683689988.;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_51_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %+ 0Lf!\ntest: %060Lf!\ntest: %.15Lf!";
  long double num = -9325781235683689988.;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_52_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %-+.1Lf!\ntest: %- .2Lf!\ntest: %-0.3Lf!";
  long double num = -0.999999;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_54_f) {
  char str1[400];
  char str2[400];
  char *str3 = "fshgkaljck% 10.12f hgsakul";
  double num = 0.235300;
  ck_assert_int_eq(sprintf(str1, str3, num), s21_sprintf(str2, str3, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST
//MY FLOAT
START_TEST(sprintf_float_precision) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char *format = "%Lf";
    long double val = 513515.131513515151351;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_float_width) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char *format = "%10Lf";
    long double val = 15.35;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_float_precision_zero) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char *format = "%.0Lf";
    long double val = 15.35;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_float_precision_empty) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char *format = "%.Lf";
    long double val = 15.35;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_float_precision_huge) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char *format = "%.15Lf";
    long double val = 15.35;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_float_precision_huge_negative) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char *format = "%.15Lf";
    long double val = -15.35581134;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_float_huge) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char *format = "%Lf";
    long double val = 72537572375.1431341;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_float_flags) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char *format = "% f";
    float val = 0;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_float_many) {
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char *format = "% .0f %.lf %Lf %f %lf %Lf";
    float val = 0;
    double val1 = 0;
    long double val2 = 3515315.153151;
    float val3 = 5.5;
    double val4 = 9851.51351;
    long double val5 = 95919539159.53151351131;
    ck_assert_int_eq(
        s21_sprintf(str1, format, val, val1, val2, val3, val4, val5),
        sprintf(str2, format, val, val1, val2, val3, val4, val5));

    ck_assert_str_eq(str1, str2);
} END_TEST

Suite *test_sprintf_f(void) {
  Suite *s = suite_create("\033[45m-=S21_SPRINTF_F=-\033[0m");
  TCase *tc = tcase_create("sprintf_tc");

  //tcase_add_test(tc, sprintf_1_f);
  // tcase_add_test(tc, sprintf_2_f);

  tcase_add_test(tc, sprintf_3_f);
  tcase_add_test(tc, sprintf_4_f);
  tcase_add_test(tc, sprintf_5_f);

  //tcase_add_test(tc, sprintf_6_f);
  // tcase_add_test(tc, sprintf_7_f);
  // tcase_add_test(tc, sprintf_8_f);
  // tcase_add_test(tc, sprintf_9_f);
  // tcase_add_test(tc, sprintf_10_f);
  // tcase_add_test(tc, sprintf_11_f);
  // tcase_add_test(tc, sprintf_12_f);

  // tcase_add_test(tc, sprintf_13_f);
  // tcase_add_test(tc, sprintf_14_f);
  // tcase_add_test(tc, sprintf_15_f);
  // tcase_add_test(tc, sprintf_16_f);
  // tcase_add_test(tc, sprintf_17_f);
  // tcase_add_test(tc, sprintf_18_f);
  // tcase_add_test(tc, sprintf_19_f);
  // tcase_add_test(tc, sprintf_20_f);
  // tcase_add_test(tc, sprintf_21_f);
  // tcase_add_test(tc, sprintf_22_f);
  // tcase_add_test(tc, sprintf_23_f);
  // tcase_add_test(tc, sprintf_24_f);
  // tcase_add_test(tc, sprintf_25_f);
  // tcase_add_test(tc, sprintf_26_f);


  // tcase_add_test(tc, sprintf_27_f);
  // tcase_add_test(tc, sprintf_28_f);
  // tcase_add_test(tc, sprintf_30_f);
  // tcase_add_test(tc, sprintf_31_f);
  // tcase_add_test(tc, sprintf_32_f);
  // tcase_add_test(tc, sprintf_33_f);
  // tcase_add_test(tc, sprintf_34_f);
  // tcase_add_test(tc, sprintf_35_f);
  // tcase_add_test(tc, sprintf_36_f);
  // tcase_add_test(tc, sprintf_37_f);
  // tcase_add_test(tc, sprintf_38_f);
  // tcase_add_test(tc, sprintf_39_f);
  // tcase_add_test(tc, sprintf_40_f);
  // tcase_add_test(tc, sprintf_41_f);
  // tcase_add_test(tc, sprintf_42_f);
  // tcase_add_test(tc, sprintf_43_f);
  // tcase_add_test(tc, sprintf_44_f);
  // tcase_add_test(tc, sprintf_45_f);
  // tcase_add_test(tc, sprintf_46_f);
  // tcase_add_test(tc, sprintf_47_f);
  // tcase_add_test(tc, sprintf_48_f);
  // tcase_add_test(tc, sprintf_49_f);
  // tcase_add_test(tc, sprintf_50_f);
  // tcase_add_test(tc, sprintf_51_f);
  // tcase_add_test(tc, sprintf_52_f);
  // tcase_add_test(tc, sprintf_54_f);


    // tcase_add_test(tc, sprintf_float_precision);
    // tcase_add_test(tc, sprintf_float_width);
    // tcase_add_test(tc, sprintf_float_precision_zero);
    // tcase_add_test(tc, sprintf_float_precision_empty);
    // tcase_add_test(tc, sprintf_float_precision_huge);
    // tcase_add_test(tc, sprintf_float_precision_huge_negative);
    // tcase_add_test(tc, sprintf_float_huge);
    // tcase_add_test(tc, sprintf_float_flags);
    // tcase_add_test(tc, sprintf_float_many);
  suite_add_tcase(s, tc);
  return s;
}


int main(void) {
    setlocale(LC_ALL, "en_US.UTF-8");
    int nf;
    Suite *s1;
    SRunner *sr;
    s1 = test_sprintf_f();
    sr = srunner_create(s1);

    //srunner_run_all(sr, CK_ENV);
    //srunner_run_all(sr, CK_NORMAL);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_VERBOSE);

    nf = srunner_ntests_failed(sr);
    //srunner_free(sr);
    return nf == 0 ? 0 : 1;
}
