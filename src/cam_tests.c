#include <stdlib.h>
#include <check.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

#include "alltests.h"

//#define BUFF_SIZE 512

// strchr

START_TEST(strchr_1) {
    char str_1[] = "ABCDEFGH\0";
    char chr = 'A';
    ck_assert_pstr_eq(strchr(str_1, chr), s21_strchr(str_1, chr));
} END_TEST

START_TEST(strchr_2) {
    char str_1[] = "ABCDEFGH\0";
    ck_assert_pstr_eq(strchr(str_1, '0'), s21_strchr(str_1, '0'));
} END_TEST

START_TEST(strchr_3) {
    char str_1[] = "ABCDEFGH\0";
    ck_assert_pstr_eq(strchr(str_1, 'H'), s21_strchr(str_1, 'H'));
} END_TEST

START_TEST(strchr_4) {
    char *str_1 = "ABCDEF~DGH\0";
    ck_assert_pstr_eq(strchr(str_1, 'D'), s21_strchr(str_1, 'D'));
} END_TEST

START_TEST(strchr_5) {
    char str_1[] = "";
    char chr = 'D';
    ck_assert_pstr_eq(strchr(str_1, chr), s21_strchr(str_1, chr));
} END_TEST

START_TEST(strchr_6) {
    char *str_1 = "";
    ck_assert_pstr_eq(strchr(str_1, '\0'), s21_strchr(str_1, '\0'));
} END_TEST

START_TEST(strchr_7) {
    char *str_1 = "ABCDEFGH\0";
    ck_assert_pstr_eq(strchr(str_1, '\0'), s21_strchr(str_1, '\0'));
} END_TEST

// strrchr

START_TEST(strrchr_1) {
    char *str_1 = "ABCDEFasaGH\0";
    ck_assert_pstr_eq(strchr(str_1, 'a'), s21_strchr(str_1, 'a'));
} END_TEST

START_TEST(strrchr_2) {
    char *str_1 = "ABCDEFasaGH\0";
    ck_assert_pstr_eq(strchr(str_1, 'A'), s21_strchr(str_1, 'A'));
} END_TEST

START_TEST(strrchr_3) {
    char *str_1 = "ABCDEFasaGH\0";
    ck_assert_pstr_eq(strchr(str_1, '\0'), s21_strchr(str_1, '\0'));
} END_TEST

START_TEST(strrchr_4) {
    char *str_1 = "ABCDEFasaGH\0";
    ck_assert_pstr_eq(strchr(str_1, '5'), s21_strchr(str_1, '5'));
} END_TEST

START_TEST(strrchr_5) {
    char *str_1 = "";
    ck_assert_pstr_eq(strchr(str_1, 'A'), s21_strchr(str_1, 'A'));
} END_TEST

START_TEST(strrchr_6) {
    char *str_1 = "\0A\0";
    ck_assert_pstr_eq(strchr(str_1, '\0'), s21_strchr(str_1, '\0'));
} END_TEST

START_TEST(strrchr_7) {
    char *str_1 = "";
    ck_assert_pstr_eq(strchr(str_1, '\0'), s21_strchr(str_1, '\0'));
} END_TEST


// strbrk

START_TEST(strpbrk_1) {
    char str[]= "this_is_a_";
    ck_assert_pstr_eq(strpbrk(str, "369"), s21_strpbrk(str, "369"));
} END_TEST

START_TEST(strpbrk_2) {
    char str2[] = "camarrod";
    ck_assert_pstr_eq(strpbrk(str2, "fzx"), s21_strpbrk(str2, "fzx"));
} END_TEST

START_TEST(strpbrk_3) {
    char str3[] = {'q', 'r', 's', 't', 'w', 's', 'a', 's', '\0'};
    ck_assert_pstr_eq(strpbrk(str3, "saq"), s21_strpbrk(str3, "saq"));
} END_TEST

START_TEST(strpbrk_4) {
    char str1[] = "";
    char str2[] = "";
    ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
} END_TEST

START_TEST(strpbrk_5) {
    char str1[] = "Camarrod";
    char str2[] = "";
    ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
} END_TEST

START_TEST(strpbrk_6) {
    char str1[] = "";
    char str2[] = "ICL";
    ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
} END_TEST

START_TEST(strpbrk_7) {
    char str1[] = "--branch=branch-name";
    char str2[] = "b";
    ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
} END_TEST

START_TEST(strpbrk_8) {
    char str1[] = "--branch=branch-name";
    char str2[] = "a";
    ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
} END_TEST

START_TEST(strpbrk_9) {
    char str1[] = "--branch=branch-name";
    char str2[] = "3";
    ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
} END_TEST

START_TEST(strpbrk_10) {
    char str1[] = "ppppppppppppP";
    char str2[] = "P";
    ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
} END_TEST

START_TEST(strpbrk_11) {
    char str1[] = "ppppppppppppP";
    char str2[] = "\0";
    ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
} END_TEST

// STRBRK END

// MEMCHR

START_TEST(memchr_1) {
    s21_size_t n = 6;
    char str1[] = "--branch=branch-name";
    //char str2[] = "--branch=branch-name";
    ck_assert_ptr_eq(s21_memchr(str1, 'a', n), memchr(str1, 'a', n));
} END_TEST


START_TEST(memchr_2) {
    s21_size_t n = 7;
    char str1[] = "--branch=branch-name";
    //char str2[] = "--branch=branch-name";
    ck_assert_ptr_eq(s21_memchr(str1, '=', n), memchr(str1, '=', n));
} END_TEST

START_TEST(memchr_3) {
    s21_size_t n = 7;
    char str1[] = "Camarrod";
    //char str2[] = "Camarrod";
    ck_assert_ptr_eq(s21_memchr(str1, 'u', n), memchr(str1, 'u', n));
} END_TEST


START_TEST(memchr_4) {
    s21_size_t n = 1;
    char str1[] = "";
    //char str2[] = "";
    ck_assert_ptr_eq(s21_memchr(str1, 'A', n), memchr(str1, 'A', n));
} END_TEST


START_TEST(memchr_5) {
    s21_size_t n = 20;
    char str1[] = "--branch=branch-namE";
    //char str2[] = "--branch=branch-name";
    ck_assert_ptr_eq(s21_memchr(str1, 'E', n), memchr(str1, 'E', n));
} END_TEST

START_TEST(memchr_6) {
    s21_size_t n = 0;
    char str1[] = "";
    //char str2[] = "";
    ck_assert_ptr_eq(s21_memchr(str1, 'a', n), memchr(str1, 'a', n));
} END_TEST

START_TEST(memchr_7) {
    s21_size_t n = 17;
    char str1[] = "--branch=branch-Dname";
    //char str2[] = "--branch=branch-Dname";
    ck_assert_ptr_eq(s21_memchr(str1, 'D', n), memchr(str1, 'D', n));
} END_TEST

START_TEST(memchr_8) {
    s21_size_t n = 6;
    char str1[] = "value";
    //char str2[] = "--branch=branch-Dname";
    ck_assert_ptr_eq(s21_memchr(str1, '\0', n), memchr(str1, '\0', n));
} END_TEST

START_TEST(memchr_9) {
    s21_size_t n = 6;
    int str1[] = {1, 43, 123, 43, 124, 342};
    //char str2[] = "--branch=branch-Dname";
    ck_assert_ptr_eq(s21_memchr(str1, 342, n), memchr(str1, 342, n));
} END_TEST


// MEMCHR END


//////////////

// STRSTR START

START_TEST(strstr_1) {
    char haystack[] = "Hello world !";
    char needle[] = "world";
    ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
} END_TEST


START_TEST(strstr_2) {
    char haystack[] = "Hello world !";
    char needle[] = "Hello world !";
    ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
} END_TEST

START_TEST(strstr_3) {
    char haystack[] = "Hello world !";
    char needle[] = "ABCD";
    ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
} END_TEST


START_TEST(strstr_4) {
    char haystack[] = "XML logging";
    char needle[] = "XML logging can be enabled";
    ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
} END_TEST

START_TEST(strstr_5) {
    char haystack[] = "void int XML loggXMLing";
    char needle[] = "XML";
    ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
} END_TEST


START_TEST(strstr_6) {
    char haystack[] = "";
    char needle[] = "XML";
    ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
} END_TEST

START_TEST(strstr_7) {
    char haystack[] = "";
    char needle[] = "";
    ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
} END_TEST

START_TEST(strstr_8) {
    char haystack[] = "tcase_add_test";
    char needle[] = "\0";
    ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
} END_TEST

START_TEST(strstr_9) {
    char haystack[] = "";
    char needle[] = "\0";
    ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
} END_TEST

// STRSTR END

///////////////

// MEMCPY START

START_TEST(memcpy_1) {
    char src[] = "People who had a great contribution";
    s21_size_t n = 5;
    char dest[n + 8];
    char res[n + 8];
    memcpy(dest, src, n);
    s21_memcpy(res, src, n); 
    ck_assert_mem_eq(dest, res, n);
} END_TEST

START_TEST(memcpy_2) {
    char src[] = "People who had a great contribution";
    s21_size_t n = 1;
    char dest[n + 8];
    char res[n + 8];
    memcpy(dest, src, n);
    s21_memcpy(res, src, n); 
    ck_assert_mem_eq(dest, res, n);
} END_TEST

START_TEST(memcpy_3) {
    char src[] = "People";
    s21_size_t n = 10;
    char dest[n + 8];
    char res[n + 8];
    memcpy(dest, src, n);
    s21_memcpy(res, src, n); 
    ck_assert_mem_eq(dest, res, n);
} END_TEST

START_TEST(memcpy_4) {
    char src[] = "contribution";
    s21_size_t n = 0;
    char dest[n + 8];
    char res[n + 8];
    memcpy(dest, src, n);
    s21_memcpy(res, src, n); 
    ck_assert_mem_eq(dest, res, n);
} END_TEST

START_TEST(memcpy_5) {
    char src[] = "100";
    s21_size_t n = 1;
    char dest[n + 8];
    char res[n + 8];
    memcpy(dest, src, n);
    s21_memcpy(res, src, n); 
    ck_assert_mem_eq(dest, res, n);
} END_TEST

START_TEST(memcpy_6) {
    char src[] = "";
    s21_size_t n = 0;
    char dest[n + 8];
    char res[n + 8];
    memcpy(dest, src, n);
    s21_memcpy(res, src, n); 
    ck_assert_mem_eq(dest, res, n);
} END_TEST

START_TEST(memcpy_7) {
    char src[] = "People who had a great contributionconst char *str, const char *format";
    s21_size_t n = 70;
    char dest[n + 8];
    char res[n + 8];
    memcpy(dest, src, n);
    s21_memcpy(res, src, n); 
    ck_assert_mem_eq(dest, res, n);
} END_TEST

// MEMCPY END


// STRCPY START

START_TEST(strcpy_1) {
    char src[] = "People who had a great contributionconst char *str, const char *format";
    char dest[100] = "";
    char res[100] = "";
    strcpy(dest, src);
    s21_strcpy(res, src); 
    ck_assert_str_eq(dest, res);
} END_TEST

START_TEST(strcpy_2) {
    char src[] = "People ";
    char dest[100] = "Who w w - ";
    char res[100] = "Who w w - ";
    strcpy(dest, src);
    s21_strcpy(res, src); 
    ck_assert_str_eq(dest, res);
} END_TEST

START_TEST(strcpy_3) {
    char src[] = "";
    char dest[10] = "Hello";
    char res[10] = "Hello";
    strcpy(dest, src);
    s21_strcpy(res, src); 
    ck_assert_str_eq(dest, res);
} END_TEST

START_TEST(strcpy_4) {
    char src[] = "";
    char dest[5] = "";
    char res[5] = "";
    strcpy(dest, src);
    s21_strcpy(res, src); 
    ck_assert_str_eq(dest, res);
} END_TEST

START_TEST(strcpy_5) {
    char src[] = "People ";
    char dest[100] = "\0";
    char res[100] = "\0";
    strcpy(dest, src);
    s21_strcpy(res, src); 
    ck_assert_str_eq(dest, res);
} END_TEST

START_TEST(strcpy_6) {
    char src[] = "\0";
    char dest[10] = "People";
    char res[10] = "People";
    strcpy(dest, src);
    s21_strcpy(res, src); 
    ck_assert_str_eq(dest, res);
} END_TEST

START_TEST(strcpy_7) {
    char src[] = "People who had a great contributionconst ";
    char dest[100] = "Here we will copy all n characters in the temp ";
    char res[100] = "Here we will copy all n characters in the temp ";
    strcpy(dest, src);
    s21_strcpy(res, src); 
    ck_assert_str_eq(dest, res);
} END_TEST


START_TEST(strcpy_8) {
    char src[] = "ABCD\0FDCD";
    char dest[20] = "P\"eo\0ple";
    char res[20] = "P\"eo\0ple";
    strcpy(dest, src);
    s21_strcpy(res, src); 
    ck_assert_str_eq(dest, res);
} END_TEST

// STRCPY END


// STRNCPY START

START_TEST(strncpy_1) {
    char src[] = "People who had a great contributionconst char *str, const char *format";
    char dest[100] = "";
    char res[100] = "";
    s21_size_t n = 10;
    strncpy(dest, src, n);
    s21_strncpy(res, src, n); 
    ck_assert_str_eq(dest, res);
} END_TEST

START_TEST(strncpy_2) {
    char src[] = "People ";
    char dest[100] = "Who w w - ";
    char res[100] = "Who w w - ";
    s21_size_t n = 20;
    strncpy(dest, src, n);
    s21_strncpy(res, src, n); 
    ck_assert_str_eq(dest, res);
} END_TEST

START_TEST(strncpy_3) {
    char src[] = "";
    char dest[10] = "Hello";
    char res[10] = "Hello";
    s21_size_t n = 2;
    strncpy(dest, src, n);
    s21_strncpy(res, src, n); 
    ck_assert_str_eq(dest, res);
} END_TEST

START_TEST(strncpy_4) {
    char src[] = "";
    char dest[5] = "";
    char res[5] = "";
    s21_size_t n = 2;
    strncpy(dest, src, n);
    s21_strncpy(res, src, n); 
    ck_assert_str_eq(dest, res);
} END_TEST

START_TEST(strncpy_5) {
    char src[] = "People ";
    char dest[100] = "\0";
    char res[100] = "\0";
    s21_size_t n = 0;
    strncpy(dest, src, n);
    s21_strncpy(res, src, n); 
    ck_assert_str_eq(dest, res);
} END_TEST

START_TEST(strncpy_6) {
    char src[] = "\0";
    char dest[10] = "People";
    char res[10] = "People";
    s21_size_t n = 1;
    strncpy(dest, src, n);
    s21_strncpy(res, src, n); 
    ck_assert_str_eq(dest, res);
} END_TEST

START_TEST(strncpy_7) {
    char src[] = "People who had a great contributionconst ";
    char dest[100] = "Here we will copy all n characters in the temp ";
    char res[100] = "Here we will copy all n characters in the temp ";
    s21_size_t n = 15;
    strncpy(dest, src, n);
    s21_strncpy(res, src, n); 
    ck_assert_str_eq(dest, res);
} END_TEST


START_TEST(strncpy_8) {
    char src[] = "ABCD\0FDCD";
    char dest[20] = "P\"eo\0ple";
    char res[20] = "P\"eo\0ple";
    s21_size_t n = 6;
    strncpy(dest, src, n);
    s21_strncpy(res, src, n); 
    ck_assert_str_eq(dest, res);
} END_TEST

// STRNCPY END

// MEMSET START

START_TEST(memset_1) {
    char res[] = "Hello";
    char exp[] = "Hello";
    char replace = 'D';
    s21_size_t n = 3;
    s21_memset(res, replace, n);
    memset(exp, replace, n);
    ck_assert_str_eq(res, exp);
} END_TEST

START_TEST(memset_2) {
    char res[] = "Hello";
    char exp[] = "Hello";
    char replace = 'D';
    s21_size_t n = 0;
    s21_memset(res, replace, n);
    memset(exp, replace, n);
    ck_assert_str_eq(res, exp);
} END_TEST

START_TEST(memset_3) {
    char res[] = "Hello";
    char exp[] = "Hello";
    char replace = 'D';
    s21_size_t n = 5;
    s21_memset(res, replace, n);
    memset(exp, replace, n);
    ck_assert_str_eq(res, exp);
} END_TEST


START_TEST(memset_4) {
    char res[] = "\0";
    char exp[] = "\0";
    char replace = 'D';
    s21_size_t n = 1;
    s21_memset(res, replace, n);
    memset(exp, replace, n);
    ck_assert_str_eq(res, exp);
} END_TEST

START_TEST(memset_5) {
    char res[] = "aaa";
    char exp[] = "aaa";
    char replace = 'a';
    s21_size_t n = 3;
    s21_memset(res, replace, n);
    memset(exp, replace, n);
    ck_assert_str_eq(res, exp);
} END_TEST

START_TEST(memset_6) {
    char res[] = "QWERTYUIOP[]ASDFGHJKL;'\\ZXCVBNM,./";
    char exp[] = "QWERTYUIOP[]ASDFGHJKL;'\\ZXCVBNM,./";
    char replace = '0';
    s21_size_t n = 10;
    s21_memset(res, replace, n);
    memset(exp, replace, n);
    ck_assert_str_eq(res, exp);
} END_TEST

START_TEST(memset_7) {
    char res[] = "HELLO W\0ORLD !";
    char exp[] = "HELLO W\0ORLD !";
    char replace = '_';
    s21_size_t n = 11;
    s21_memset(res, replace, n);
    memset(exp, replace, n);
    ck_assert_str_eq(res, exp);
} END_TEST

// MEMSET END

// TO UPPER START

START_TEST(to_upper_1) {
    char str1[] = "hEllO, WoRLD!";
    char *str2 = (char *)s21_to_upper(str1);
    ck_assert_pstr_eq(str2, "HELLO, WORLD!");
    free(str2);
} END_TEST

START_TEST(to_upper_2) {
    char str1[] = "hEllO, WoRLD! 123#23";
    char *str2 = (char *)s21_to_upper(str1);
    ck_assert_pstr_eq(str2, "HELLO, WORLD! 123#23");
    free(str2);
} END_TEST

START_TEST(to_upper_3) {
    char str1[] = "1234567890";
    char *str2 = (char *)s21_to_upper(str1);
    ck_assert_pstr_eq(str2, "1234567890");
    free(str2);
} END_TEST

START_TEST(to_upper_4) {
    char str1[] = "asdfQWER 1020 HeLlO";
    char *str2 = (char *)s21_to_upper(str1);
    ck_assert_pstr_eq(str2, "ASDFQWER 1020 HELLO");
    free(str2);
} END_TEST

// TO UPPER END

// INSERT START

START_TEST(insert_1) {
    char *str = "Implemion";
    char *str2;
    str2 = s21_insert(str, "entat", 6);
    ck_assert_pstr_eq(str2, "Implementation");
    free(str2);
} END_TEST


START_TEST(insert_2) {
    char *str = "ABC";
    char *str2;
    str2 = s21_insert(str, "DEF", 3);
    ck_assert_pstr_eq(str2, "ABCDEF");
    free(str2);
} END_TEST

START_TEST(insert_3) {
    char str[] = "Implementrs";
    char *str2;
    str2 = s21_insert(str, "ation", 20);
    ck_assert_pstr_eq(str2, s21_NULL);
    free(str2);
} END_TEST

START_TEST(insert_4) {
    char *str = s21_NULL;
    char *str2;
    str2 = s21_insert(str, "ation", 9);
    ck_assert_pstr_eq(str2, s21_NULL);
    free(str2);
} END_TEST

START_TEST(insert_5) {
    char str[] = "";
    char src[] = "";
    s21_size_t index = 1;
    char *expected = s21_NULL;
    char *got = (char *)s21_insert(src, str, index);
    ck_assert_pstr_eq(got, expected);
    if (got)
        free(got);
} END_TEST

START_TEST(insert_6) {
    char str[] = "Hello ";
    char src[] = "World ";
    s21_size_t index = 6;
    char expected[] = "World Hello ";
    char *got = (char *)s21_insert(src, str, index);
    ck_assert_str_eq(got, expected);
    if (got)
        free(got);
} END_TEST

START_TEST(insert_7) {
    char *str = s21_NULL;
    char *src = s21_NULL;
    s21_size_t index = 3;
    char *expected = s21_NULL;
    char *got = (char *)s21_insert(src, str, index);
    ck_assert_pstr_eq(got, expected);
    if (got)
        free(got);
} END_TEST

// INSERT END

// MEMMOVE START

START_TEST(memmove_1) {
    char src1[] = "russian version of the task can be";
    char src2[] = "russian version of the task can be";
    s21_size_t n = 20;
    char res[100] = "Hello !@#!";
    char expected[100] = "Hello !@#!";
    s21_memmove(res, src1, n);
    memmove(expected, src2, n);
    ck_assert_pstr_eq(res, expected);
} END_TEST

START_TEST(memmove_2) {
    char src1[] = "";
    char src2[] = "";
    s21_size_t n = 5;
    char res[100] = "Hello !@#!";
    char expected[100] = "Hello !@#!";
    s21_memmove(res, src1, n);
    memmove(expected, src2, n);
    ck_assert_pstr_eq(res, expected);
} END_TEST

START_TEST(memmove_3) {
    char src1[] = "russian version of the task can be";
    char src2[] = "russian version of the task can be";
    s21_size_t n = 20;
    char res[30] = "Hello !@#!";
    char expected[30] = "Hello !@#!";
    s21_memmove(res, src1, n);
    memmove(expected, src2, n);
    ck_assert_pstr_eq(res, expected);
} END_TEST

START_TEST(memmove_4) {
    char src1[] = "aSD123fg!@\b\0ada";
    char src2[] = "aSD123fg!@\b\0ada";
    s21_size_t n = 5;
    char res[100] = "";
    char expected[100] = "";
    s21_memmove(res, src1, n);
    memmove(expected, src2, n);
    ck_assert_pstr_eq(res, expected);
} END_TEST


START_TEST(memmove_5) {
    char src1[] = "1234567890ASDFGHJK asd";
    char src2[] = "1234567890ASDFGHJK asd";
    s21_size_t n = 5;
    s21_size_t position = 10;
    char *res = src1 + position;
    char *expected = res = src2 + position;
    s21_memmove(res, src1, n);
    memmove(expected, src2, n);
    ck_assert_pstr_eq(res, expected);
} END_TEST

START_TEST(memmove_6) {
    char src1[] = "\0";
    char src2[] = "\0";
    s21_size_t n = 1;
    char res[] = "";
    char expected[] = "";
    s21_memmove(res, src1, n);
    memmove(expected, src2, n);
    ck_assert_pstr_eq(res, expected);
} END_TEST

START_TEST(memmove_7) {
    char src1[] = "Apple <>";
    char src2[] = "Apple <>";
    s21_size_t n = 0;
    char res[] = "";
    char expected[] = "";
    s21_memmove(res, src1, n);
    memmove(expected, src2, n);
    ck_assert_pstr_eq(res, expected);
} END_TEST

// MEMMOVE END

Suite *test_camarrod_string_funcs(void) {
    Suite *s = suite_create("suite_insert");
    TCase *tc = tcase_create("insert_tc");

    //STRCHR
    tcase_add_test(tc, strchr_1);
    tcase_add_test(tc, strchr_2);
    tcase_add_test(tc, strchr_3);
    tcase_add_test(tc, strchr_4);
    tcase_add_test(tc, strchr_5);
    tcase_add_test(tc, strchr_6);
    tcase_add_test(tc, strchr_7);


    //STRRCHR
    tcase_add_test(tc, strrchr_1);
    tcase_add_test(tc, strrchr_2);
    tcase_add_test(tc, strrchr_3);
    tcase_add_test(tc, strrchr_4);
    tcase_add_test(tc, strrchr_5);
    tcase_add_test(tc, strrchr_6);
    tcase_add_test(tc, strrchr_7);

    //STRPBRK

    tcase_add_test(tc, strpbrk_1);
    tcase_add_test(tc, strpbrk_2);
    tcase_add_test(tc, strpbrk_3);
    tcase_add_test(tc, strpbrk_4);
    tcase_add_test(tc, strpbrk_5);
    tcase_add_test(tc, strpbrk_6);
    tcase_add_test(tc, strpbrk_7);
    tcase_add_test(tc, strpbrk_8);
    tcase_add_test(tc, strpbrk_9);
    tcase_add_test(tc, strpbrk_10);
    tcase_add_test(tc, strpbrk_11);

    // 

    tcase_add_test(tc, memchr_1);
    tcase_add_test(tc, memchr_2);
    tcase_add_test(tc, memchr_3);
    tcase_add_test(tc, memchr_4);
    tcase_add_test(tc, memchr_5);
    tcase_add_test(tc, memchr_6);
    tcase_add_test(tc, memchr_7);
    tcase_add_test(tc, memchr_8);
    tcase_add_test(tc, memchr_9);

    // STRSTR

    tcase_add_test(tc, strstr_1);
    tcase_add_test(tc, strstr_2);
    tcase_add_test(tc, strstr_3);
    tcase_add_test(tc, strstr_4);
    tcase_add_test(tc, strstr_5);
    tcase_add_test(tc, strstr_6);
    tcase_add_test(tc, strstr_7);
    tcase_add_test(tc, strstr_8);
    tcase_add_test(tc, strstr_9);
    
    // MEMCPY
    
    tcase_add_test(tc, memcpy_1);
    tcase_add_test(tc, memcpy_2);
    tcase_add_test(tc, memcpy_3);
    tcase_add_test(tc, memcpy_4);
    tcase_add_test(tc, memcpy_5);
    tcase_add_test(tc, memcpy_6);
    tcase_add_test(tc, memcpy_7);

    // STRCPY

    tcase_add_test(tc, strcpy_1);
    tcase_add_test(tc, strcpy_2);
    tcase_add_test(tc, strcpy_3);
    tcase_add_test(tc, strcpy_4);
    tcase_add_test(tc, strcpy_5);
    tcase_add_test(tc, strcpy_6);
    tcase_add_test(tc, strcpy_7);
    tcase_add_test(tc, strcpy_8);

    // STRNCPY

    tcase_add_test(tc, strncpy_1);
    tcase_add_test(tc, strncpy_2);
    tcase_add_test(tc, strncpy_3);
    tcase_add_test(tc, strncpy_4);
    tcase_add_test(tc, strncpy_5);
    tcase_add_test(tc, strncpy_6);
    tcase_add_test(tc, strncpy_7);
    tcase_add_test(tc, strncpy_8);

    // MEMSET

    tcase_add_test(tc, memset_1);
    tcase_add_test(tc, memset_2);
    tcase_add_test(tc, memset_3);
    tcase_add_test(tc, memset_4);
    tcase_add_test(tc, memset_5);
    tcase_add_test(tc, memset_6);
    tcase_add_test(tc, memset_7);

    // TO UPPER

    tcase_add_test(tc, to_upper_1);
    tcase_add_test(tc, to_upper_2);
    tcase_add_test(tc, to_upper_3);
    tcase_add_test(tc, to_upper_4);

    // INSERT

    tcase_add_test(tc, insert_1);
    tcase_add_test(tc, insert_2);
    tcase_add_test(tc, insert_3);
    tcase_add_test(tc, insert_4);
    tcase_add_test(tc, insert_5);
    tcase_add_test(tc, insert_6);
    tcase_add_test(tc, insert_7);

    // MEMMOVE

    tcase_add_test(tc, memmove_1);
    tcase_add_test(tc, memmove_2);
    tcase_add_test(tc, memmove_3);
    tcase_add_test(tc, memmove_4);
    tcase_add_test(tc, memmove_5);
    tcase_add_test(tc, memmove_6);
    tcase_add_test(tc, memmove_7);

    suite_add_tcase(s, tc);
    return s;
}


// int main(void) {
//     setlocale(LC_ALL, "");
//     int nf;
//     Suite *s1;
//     SRunner *sr;
//     s1 = suite_insert();
//     sr = srunner_create(s1);

//     // srunner_run_all(sr, CK_ENV);
//     srunner_set_fork_status(sr, CK_NOFORK);
//     srunner_run_all(sr, CK_VERBOSE);

//     nf = srunner_ntests_failed(sr);
//     srunner_free(sr);
//     return nf == 0 ? 0 : 1;
// }