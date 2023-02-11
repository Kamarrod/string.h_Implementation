#include "alltests.h"
int sameSigns(int first, int second) {
  int result = 0;
  if(first * second > 0 || (first == 0 && second == 0))
    result = 1;
  return result;
}

// ---------------------------------------------------------------------------------------------------------------

START_TEST (strlenSimple) {
  ck_assert_int_eq(s21_strlen("abc"), strlen("abc"));
} END_TEST

START_TEST (strlenEmptyString) {
  ck_assert_int_eq(s21_strlen(""), strlen(""));
} END_TEST

START_TEST (strlenOneLetterString) {
  char* str = "a";
  ck_assert_int_eq(s21_strlen("a"), strlen("a"));
  ck_assert_int_eq(s21_strlen(str), strlen(str));
} END_TEST

START_TEST (strlenOneLetterStringWithNull) {
  ck_assert_int_eq(s21_strlen("a\0"), strlen("a\0"));
} END_TEST

// ---------------------------------------------------------------------------------------------------------------

START_TEST (toLowerDiffLetters) {
  char* result = s21_to_lower("AbcDR");
  ck_assert_str_eq(result, "abcdr");
  free(result);
} END_TEST

START_TEST (toLowerAllLettersLow) {
  char* result = s21_to_lower("abcdr");
  ck_assert_str_eq(result, "abcdr");
  free(result);
} END_TEST

START_TEST (toLowerAllLettersBig) {
  char* result = s21_to_lower("ABCDR");
  ck_assert_str_eq(result, "abcdr");
  free(result);
} END_TEST

START_TEST (toLowerEmptyString) {
  char* result = s21_to_lower("");
  ck_assert_str_eq(result, "");
  free(result);
} END_TEST

START_TEST (toLowerDigits) {
  char* result = s21_to_lower("123");
  ck_assert_str_eq(result, "123");
  free(result);
} END_TEST

START_TEST (toLowerDigitsAndLetters) {
  char* result = s21_to_lower("aBC45qPR");
  ck_assert_str_eq(result, "abc45qpr");
  free(result);
} END_TEST

START_TEST (toLowerOtherSymbols) {
  char* result = s21_to_lower("!@#$^&*()_-+={[]}:;\"'|\\~`<>,.?/");
  ck_assert_str_eq(result, "!@#$^&*()_-+={[]}:;\"'|\\~`<>,.?/");
  free(result);
} END_TEST

// ---------------------------------------------------------------------------------------------------------------

START_TEST (strerrorAllErrors) {
  for(int errnum = -100; errnum < 200; ++errnum)
    ck_assert_str_eq(s21_strerror(errnum), strerror(errnum));
} END_TEST

// ---------------------------------------------------------------------------------------------------------------

START_TEST (strcmpSameStringsSmallLetters) {
  ck_assert(sameSigns(s21_strcmp("abc", "abc"), strcmp("abc", "abc")) == 1);
} END_TEST

START_TEST (strcmpSameStringsBigLetters) {
  ck_assert(sameSigns(s21_strcmp("QWE", "QWE"), strcmp("QWE", "QWE")) == 1);
} END_TEST

START_TEST (strcmpSameStringsDiffLetters) {
  ck_assert(sameSigns(s21_strcmp("abcRtaeW", "abcRtaeW"), strcmp("abcRtaeW", "abcRtaeW")) == 1);
} END_TEST

START_TEST (strcmpSameStringsDigits) {
  ck_assert(sameSigns(s21_strcmp("1234567890", "1234567890"), strcmp("1234567890", "1234567890")) == 1);
} END_TEST

START_TEST (strcmpSameStringsOtherSymbols) {
  ck_assert(sameSigns(s21_strcmp("!@#$^&*()_-+={[]}:;\"'|\\~`<>,.?/", "!@#$^&*()_-+={[]}:;\"'|\\~`<>,.?/"),
    strcmp("!@#$^&*()_-+={[]}:;\"'|\\~`<>,.?/", "!@#$^&*()_-+={[]}:;\"'|\\~`<>,.?/")) == 1);
} END_TEST

START_TEST (strcmpDiffStringsOtherSymbols) {
  ck_assert(sameSigns(s21_strcmp("!@#$^&*()_-+={[]}:;\"'|\\~`<>,.?/", "!@#$^&*()_-+={[]}:;\"'|\\~`<>"),
    strcmp("!@#$^&*()_-+={[]}:;\"'|\\~`<>,.?/", "!@#$^&*()_-+={[]}:;\"'|\\~`<>")) == 1);
} END_TEST

START_TEST (strcmpSameStringsJustSpaces) {
  ck_assert(sameSigns(s21_strcmp("   ", "   "),
    strcmp("   ", "   ")) == 1);
} END_TEST

START_TEST (strcmpEmptyStrings) {
  ck_assert(sameSigns(s21_strcmp("", ""), strcmp("", "")) == 1);
} END_TEST

START_TEST (strcmpDigits1) {
  ck_assert(sameSigns(s21_strcmp("123", "039"), strcmp("123", "039")) == 1);
} END_TEST

START_TEST (strcmpDigits2) {
  ck_assert(sameSigns(s21_strcmp("123", "124"), strcmp("123", "124")) == 1);
} END_TEST

START_TEST (strcmpSpaces) {
  ck_assert(sameSigns(s21_strcmp("", "  "), strcmp("", "  ") ) == 1);
} END_TEST

START_TEST (strcmpDiffLengthStr1) {
  ck_assert(sameSigns(s21_strcmp("123", "12345"), strcmp("123", "12345")) == 1);
} END_TEST

START_TEST (strcmpDiffLengthStr2) {
  ck_assert(sameSigns(s21_strcmp("abcdr", "abc"), strcmp("abcdr", "abc")) == 1);
} END_TEST

// ---------------------------------------------------------------------------------------------------------------

START_TEST (memcmpSameStringsSmallLetters) {
  for(size_t i = 0; i < 5; ++i)
    ck_assert(sameSigns(s21_memcmp("abc", "abc", i), memcmp("abc", "abc", i)) == 1);
} END_TEST


START_TEST (memcmpSameStringsBigLetters) {
  for(size_t i = 0; i < 5; ++i)
    ck_assert(sameSigns(s21_memcmp("QWE", "QWE", i), memcmp("QWE", "QWE", i)) == 1);
} END_TEST


START_TEST (memcmpSameStringsDiffLetters) {
  for(size_t i = 0; i < 15; ++i)
    ck_assert(sameSigns(s21_memcmp("abcRtaeW", "abcRtaeW", i), memcmp("abcRtaeW", "abcRtaeW", i)) == 1);
} END_TEST

START_TEST (memcmpSameStringsDigits) {
  for(size_t i = 0; i < 11; ++i)
    ck_assert(sameSigns(s21_memcmp("1234567890", "1234567890", i), memcmp("1234567890", "1234567890", i)) == 1);
} END_TEST

START_TEST (memcmpSameStringsOtherSymbols) {
  for(size_t i = 0; i < 100; ++i)
    ck_assert(sameSigns(s21_memcmp("!@#$^&*()_-+={[]}:;\"'|\\~`<>,.?/", "!@#$^&*()_-+={[]}:;\"'|\\~`<>,.?/", i),
    memcmp("!@#$^&*()_-+={[]}:;\"'|\\~`<>,.?/", "!@#$^&*()_-+={[]}:;\"'|\\~`<>,.?/", i)) == 1);
} END_TEST

START_TEST (memcmpDiffStringsOtherSymbols) {
  for(size_t i = 0; i < 100; ++i)
    ck_assert(sameSigns(s21_memcmp("!@#$^&*()_-+={[]}:;\"'|\\~`<>,.?/", "!@#$^&*()_-+={[]}:;\"'|\\~`<>", i),
    memcmp("!@#$^&*()_-+={[]}:;\"'|\\~`<>,.?/", "!@#$^&*()_-+={[]}:;\"'|\\~`<>", i)) == 1);
} END_TEST

START_TEST (memcmpSameStringsJustSpaces) {
  for(size_t i = 0; i < 5; ++i)
  ck_assert(sameSigns(s21_memcmp("   ", "   ", i),
    memcmp("   ", "   ", i)) == 1);
} END_TEST

START_TEST (memcmpEmptyStrings) {
  for(size_t i = 0; i < 5; ++i)
    ck_assert(sameSigns(s21_memcmp("", "", i), memcmp("", "", i)) == 1);
} END_TEST

START_TEST (memcmpDigits1) {
  for(size_t i = 0; i < 5; ++i)
    ck_assert(sameSigns(s21_memcmp("123", "039", i), memcmp("123", "039", i)) == 1);
} END_TEST

START_TEST (memcmpDigits2) {
  for(size_t i = 0; i < 5; ++i)
    ck_assert(sameSigns(s21_memcmp("123", "124", i), memcmp("123", "124", i)) == 1);
} END_TEST

START_TEST (memcmpSpaces) {
  for(size_t i = 1; i < 5; ++i)
    ck_assert(s21_memcmp("", "  ", i) < 0);
  ck_assert(s21_memcmp("", "  ", 0) == 0);
} END_TEST

START_TEST (memcmpDiffLengthStr1) {
  for(size_t i = 0; i < 10; ++i)
    ck_assert(sameSigns(s21_memcmp("123", "12345", i), memcmp("123", "12345", i)) == 1);
} END_TEST

START_TEST (memcmpDiffLengthStr2) {
  for(size_t i = 0; i < 10; ++i)
    ck_assert(sameSigns(s21_memcmp("abcdr", "abc", i), memcmp("abcdr", "abc", i)) == 1);
} END_TEST

// ---------------------------------------------------------------------------------------------------------------

START_TEST (strncmpSameStringsSmallLetters) {
  for(size_t i = 0; i < 5; ++i)
    ck_assert(sameSigns(s21_strncmp("abc", "abc", i), strncmp("abc", "abc", i)) == 1);
} END_TEST


START_TEST (strncmpSameStringsBigLetters) {
  for(size_t i = 0; i < 5; ++i)
    ck_assert(sameSigns(s21_strncmp("QWE", "QWE", i), strncmp("QWE", "QWE", i)) == 1);
} END_TEST


START_TEST (strncmpSameStringsDiffLetters) {
  for(size_t i = 0; i < 15; ++i)
    ck_assert(sameSigns(s21_strncmp("abcRtaeW", "abcRtaeW", i), strncmp("abcRtaeW", "abcRtaeW", i)) == 1);
} END_TEST

START_TEST (strncmpSameStringsDigits) {
  for(size_t i = 0; i < 11; ++i)
    ck_assert(sameSigns(s21_strncmp("1234567890", "1234567890", i), strncmp("1234567890", "1234567890", i)) == 1);
} END_TEST

START_TEST (strncmpSameStringsOtherSymbols) {
  for(size_t i = 0; i < 100; ++i)
    ck_assert(sameSigns(s21_strncmp("!@#$^&*()_-+={[]}:;\"'|\\~`<>,.?/", "!@#$^&*()_-+={[]}:;\"'|\\~`<>,.?/", i),
    strncmp("!@#$^&*()_-+={[]}:;\"'|\\~`<>,.?/", "!@#$^&*()_-+={[]}:;\"'|\\~`<>,.?/", i)) == 1);
} END_TEST

START_TEST (strncmpDiffStringsOtherSymbols) {
  for(size_t i = 0; i < 100; ++i)
    ck_assert(sameSigns(s21_strncmp("!@#$^&*()_-+={[]}:;\"'|\\~`<>,.?/", "!@#$^&*()_-+={[]}:;\"'|\\~`<>", i),
    strncmp("!@#$^&*()_-+={[]}:;\"'|\\~`<>,.?/", "!@#$^&*()_-+={[]}:;\"'|\\~`<>", i)) == 1);
} END_TEST

START_TEST (strncmpSameStringsJustSpaces) {
  for(size_t i = 0; i < 5; ++i)
  ck_assert(sameSigns(s21_strncmp("   ", "   ", i),
    strncmp("   ", "   ", i)) == 1);
} END_TEST

START_TEST (strncmpEmptyStrings) {
  for(size_t i = 0; i < 5; ++i)
    ck_assert(sameSigns(s21_strncmp("", "", i), strncmp("", "", i)) == 1);
} END_TEST

START_TEST (strncmpDigits1) {
  for(size_t i = 0; i < 5; ++i)
    ck_assert(sameSigns(s21_strncmp("123", "039", i), strncmp("123", "039", i)) == 1);
} END_TEST

START_TEST (strncmpDigits2) {
  for(size_t i = 0; i < 5; ++i)
    ck_assert(sameSigns(s21_strncmp("123", "124", i), strncmp("123", "124", i)) == 1);
} END_TEST

START_TEST (strncmpSpaces) {
  for(size_t i = 1; i < 5; ++i)
    ck_assert(s21_strncmp("", "  ", i) < 0);
  ck_assert(s21_strncmp("", "  ", 0) == 0);
} END_TEST

START_TEST (strncmpDiffLengthStr1) {
  for(size_t i = 0; i < 10; ++i)
    ck_assert(sameSigns(s21_strncmp("123", "12345", i), strncmp("123", "12345", i)) == 1);
} END_TEST

START_TEST (strncmpDiffLengthStr2) {
  for(size_t i = 0; i < 10; ++i)
    ck_assert(sameSigns(s21_strncmp("abcdr", "abc", i), strncmp("abcdr", "abc", i)) == 1);
} END_TEST

// ---------------------------------------------------------------------------------------------------------------

START_TEST(trimSameStrings) {
  char* result = s21_trim("abc", "abc");
  ck_assert_str_eq(result, "");
} END_TEST

START_TEST(trimEmptyDeleteString) {
  char* result = s21_trim("abc", "");
  ck_assert_str_eq(result, "abc");
  free(result);
} END_TEST

START_TEST(trimDeleteEdgeSpaces) {
  char* result = s21_trim("  abc  ", " ");
  ck_assert_str_eq(result, "abc");
  free(result);
} END_TEST

START_TEST(trimOtherLetters) {
  char* result = s21_trim("abc", "rtv ");
  ck_assert_str_eq(result, "abc");
  free(result);
} END_TEST

START_TEST(trimSomeLetters) {
  char* result = s21_trim("abc", "ac");
  ck_assert_str_eq(result, "b");
  free(result);
} END_TEST

START_TEST(trimInnerLetters) {
  char* result = s21_trim("abcde", "bcd");
  ck_assert_str_eq(result, "abcde");
  free(result);
} END_TEST

START_TEST(trimEmptyStr) {
  char* result = s21_trim("", "abc");
  ck_assert_str_eq(result, "");
} END_TEST

// ---------------------------------------------------------------------------------------------------------------

START_TEST(strcatSimple) {
  char s21_first[20] = "begin";
  char s21_second[20] = "end";
  char first[20] = "begin";
  char second[20] = "end";
  ck_assert_str_eq(s21_strcat(s21_first, s21_second), strcat(first, second));
} END_TEST

START_TEST(strcatAddToEmpty) {
  char s21_first[10] = "";
  char s21_second[10] = "end";
  char first[10] = "";
  char second[10] = "end";
  ck_assert_str_eq(s21_strcat(s21_first, s21_second), strcat(first, second));
} END_TEST

START_TEST(strcatBothEmpty) {
  char s21_first[20] = "";
  char s21_second[20] = "";
  char first[20] = "";
  char second[20] = "";
  ck_assert_str_eq(s21_strcat(s21_first, s21_second), strcat(first, second));
} END_TEST

START_TEST(strcatAddEmpty) {
  char s21_first[20] = "begin";
  char s21_second[20] = "";
  char first[20] = "begin";
  char second[20] = "";
  ck_assert_str_eq(s21_strcat(s21_first, s21_second), strcat(first, second));
} END_TEST

// ---------------------------------------------------------------------------------------------------------------

START_TEST(strncatSimple1) {
  char s21_first[20] = "begin";
  char s21_second[20] = "end";
  char first[20] = "begin";
  char second[20] = "end";
  ck_assert_str_eq(s21_strncat(s21_first, s21_second, 0), strncat(first, second, 0));
} END_TEST

START_TEST(strncatSimple2) {
  char s21_first[20] = "begin";
  char s21_second[20] = "end";
  char first[20] = "begin";
  char second[20] = "end";
  ck_assert_str_eq(s21_strncat(s21_first, s21_second, 3), strncat(first, second, 3));
} END_TEST

START_TEST(strncatSimple3) {
  char s21_first[20] = "begin";
  char s21_second[20] = "end";
  char first[20] = "begin";
  char second[20] = "end";
  ck_assert_str_eq(s21_strncat(s21_first, s21_second, 10), strncat(first, second, 10));
} END_TEST

START_TEST(strncatAddToEmpty1) {
  char s21_first[10] = "";
  char s21_second[10] = "end";
  char first[10] = "";
  char second[10] = "end";
  ck_assert_str_eq(s21_strncat(s21_first, s21_second, 0), strncat(first, second, 0));
} END_TEST

START_TEST(strncatAddToEmpty2) {
  char s21_first[10] = "";
  char s21_second[10] = "end";
  char first[10] = "";
  char second[10] = "end";
  ck_assert_str_eq(s21_strncat(s21_first, s21_second, 3), strncat(first, second, 3));
} END_TEST

START_TEST(strncatAddToEmpty3) {
  char s21_first[10] = "";
  char s21_second[10] = "end";
  char first[10] = "";
  char second[10] = "end";
  ck_assert_str_eq(s21_strncat(s21_first, s21_second, 5), strncat(first, second, 5));
} END_TEST

START_TEST(strncatBothEmpty1) {
  char s21_first[20] = "";
  char s21_second[20] = "";
  char first[20] = "";
  char second[20] = "";
  ck_assert_str_eq(s21_strncat(s21_first, s21_second, 0), strncat(first, second, 0));
} END_TEST

START_TEST(strncatBothEmpty2) {
  char s21_first[20] = "";
  char s21_second[20] = "";
  char first[20] = "";
  char second[20] = "";
  ck_assert_str_eq(s21_strncat(s21_first, s21_second, 5), strncat(first, second, 5));
} END_TEST

START_TEST(strncatAddEmpty1) {
  char s21_first[20] = "begin";
  char s21_second[20] = "";
  char first[20] = "begin";
  char second[20] = "";
  ck_assert_str_eq(s21_strncat(s21_first, s21_second, 0), strncat(first, second, 0));
} END_TEST

START_TEST(strncatAddEmpty2) {
  char s21_first[20] = "begin";
  char s21_second[20] = "";
  char first[20] = "begin";
  char second[20] = "";
  ck_assert_str_eq(s21_strncat(s21_first, s21_second, 3), strncat(first, second, 3));
} END_TEST

// ---------------------------------------------------------------------------------------------------------------

START_TEST(strspnSearchSomeLetters) {
  ck_assert_int_eq(s21_strspn("qwerty", "qwe"), strspn("qwerty", "qwe"));
} END_TEST


START_TEST(strspnSearchEmpty) {
  ck_assert_int_eq(s21_strspn("qwerty", ""), strspn("qwerty", ""));
} END_TEST

START_TEST(strspnSameStrings) {
  ck_assert_int_eq(s21_strspn("qwerty", "qwerty"), strspn("qwerty", "qwerty"));
} END_TEST

START_TEST(strspnSearchInEmptyString) {
  ck_assert_int_eq(s21_strspn("", "qwe"), strspn("", "qwe"));
} END_TEST

START_TEST(strspnBothEmpty) {
  ck_assert_int_eq(s21_strspn("", ""), strspn("", ""));
} END_TEST

START_TEST(strspnSearchOtherChars) {
  ck_assert_int_eq(s21_strspn("qwerty", "abcde"), strspn("qwerty", "abcde"));
} END_TEST

START_TEST(strspnBothStringsOnlySpaces) {
  ck_assert_int_eq(s21_strspn("   ", " "), strspn("   ", " "));
} END_TEST

// ---------------------------------------------------------------------------------------------------------------

START_TEST(strcspnBothStringsOnlySpaces) {
  ck_assert_int_eq(s21_strcspn("   ", " "), strcspn("   ", " "));
} END_TEST

START_TEST(strcspnSameStrings) {
  ck_assert_int_eq(s21_strcspn("abcde", "abcde"), strcspn("abcde", "abcde"));
} END_TEST

START_TEST(strcspnDiffStrings) {
  ck_assert_int_eq(s21_strcspn("qwerty", "abcd"), strcspn("qwerty", "abcd"));
} END_TEST

START_TEST(strcspnBothStringsEmpty) {
  ck_assert_int_eq(s21_strcspn("", ""), strcspn("", ""));
} END_TEST

START_TEST(strcspnSearchInEmpty) {
  ck_assert_int_eq(s21_strcspn("", " aw"), strcspn("", " aw"));
} END_TEST

START_TEST(strcspnSameSuffix) {
  ck_assert_int_eq(s21_strcspn("abcder", " qweder"), strcspn("abcder", " qweder"));
} END_TEST

// ---------------------------------------------------------------------------------------------------------------

START_TEST(strtokSimple) {
  char s21_str[100] = "q,w.e|r t'y";
  char delim[20] = ",.| '";
  char str[100] = "q,w.e|r t'y";

  char* s21_lexems = s21_strtok(s21_str, delim);
  char* lexems = strtok(str, delim);

  while(s21_lexems) {
    ck_assert_pstr_eq(s21_lexems, lexems);
    s21_lexems = s21_strtok(NULL, delim);
    lexems = strtok(NULL, delim);
  }
} END_TEST

START_TEST(strtokEmptyDelim) {
  char s21_str[100] = "q,w.e|r t'y";
  char delim[20] = "";
  char str[100] = "q,w.e|r t'y";

  char* s21_lexems = s21_strtok(s21_str, delim);
  char* lexems = strtok(str, delim);

  while(s21_lexems) {
    ck_assert_pstr_eq(s21_lexems, lexems);
    s21_lexems = s21_strtok(NULL, delim);
    lexems = strtok(NULL, delim);
  }
} END_TEST

START_TEST(strtokSameStrs) {
  char s21_str[100] = "abacaba";
  char delim[20] = "abacaba";
  char str[100] = "abacaba";

  char* s21_lexems = s21_strtok(s21_str, delim);
  char* lexems = strtok(str, delim);

  ck_assert_pstr_eq(s21_lexems, lexems);

  while(s21_lexems) {
    ck_assert_pstr_eq(s21_lexems, lexems);
    s21_lexems = s21_strtok(NULL, delim);
    lexems = strtok(NULL, delim);
  }
} END_TEST

START_TEST(strtokBothEmpty) {
  char s21_str[100] = "";
  char delim[20] = "";
  char str[100] = "";

  char* s21_lexems = s21_strtok(s21_str, delim);
  char* lexems = strtok(str, delim);

  ck_assert_pstr_eq(s21_lexems, lexems);

  while(s21_lexems) {
    ck_assert_pstr_eq(s21_lexems, lexems);
    s21_lexems = s21_strtok(NULL, delim);
    lexems = strtok(NULL, delim);
  }
} END_TEST

START_TEST(strtokEmptyStr) {
  char s21_str[100] = "";
  char delim[20] = "ab,. ";
  char str[100] = "";

  char* s21_lexems = s21_strtok(s21_str, delim);
  char* lexems = strtok(str, delim);

  ck_assert_pstr_eq(s21_lexems, lexems);

  while(s21_lexems) {
    ck_assert_pstr_eq(s21_lexems, lexems);
    s21_lexems = s21_strtok(NULL, delim);
    lexems = strtok(NULL, delim);
  }
} END_TEST

START_TEST(strtokMatchOnlyLastLetter) {
  char s21_str[100] = "abcd";
  char delim[20] = " d";
  char str[100] = "abcd";

  char* s21_lexems = s21_strtok(s21_str, delim);
  char* lexems = strtok(str, delim);

  ck_assert_pstr_eq(s21_lexems, lexems);

  while(s21_lexems) {
    ck_assert_pstr_eq(s21_lexems, lexems);
    s21_lexems = s21_strtok(NULL, delim);
    lexems = strtok(NULL, delim);
  }
} END_TEST

START_TEST(strtokMatchMidAndLastChars) {
  char s21_str[100] = "ab cd";
  char delim[20] = " d";
  char str[100] = "ab cd";

  char* s21_lexems = s21_strtok(s21_str, delim);
  char* lexems = strtok(str, delim);

  ck_assert_pstr_eq(s21_lexems, lexems);

  while(s21_lexems) {
    ck_assert_pstr_eq(s21_lexems, lexems);
    s21_lexems = s21_strtok(NULL, delim);
    lexems = strtok(NULL, delim);
  }
} END_TEST

START_TEST(strtokMatchFromMidToEndChars) {
  char s21_str[100] = "abR cde";
  char delim[20] = " deCc";
  char str[100] = "abR cde";

  char* s21_lexems = s21_strtok(s21_str, delim);
  char* lexems = strtok(str, delim);

  ck_assert_pstr_eq(s21_lexems, lexems);

  while(s21_lexems) {
    ck_assert_pstr_eq(s21_lexems, lexems);
    s21_lexems = s21_strtok(NULL, delim);
    lexems = strtok(NULL, delim);
  }
} END_TEST

Suite* test_arboktya_string_funcs(void) {
  Suite* s = suite_create("tests");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, strlenSimple);
  tcase_add_test(tc, strlenEmptyString);
  tcase_add_test(tc, strlenOneLetterString);
  tcase_add_test(tc, strlenOneLetterStringWithNull);

  tcase_add_test(tc, toLowerDiffLetters);
  tcase_add_test(tc, toLowerAllLettersLow);
  tcase_add_test(tc, toLowerAllLettersBig);
  tcase_add_test(tc, toLowerEmptyString);
  tcase_add_test(tc, toLowerDigits);
  tcase_add_test(tc, toLowerDigitsAndLetters);
  tcase_add_test(tc, toLowerOtherSymbols);

  tcase_add_test(tc, strerrorAllErrors);

  tcase_add_test(tc, strcmpSameStringsSmallLetters);
  tcase_add_test(tc, strcmpSameStringsBigLetters);
  tcase_add_test(tc, strcmpSameStringsDiffLetters);
  tcase_add_test(tc, strcmpSameStringsDigits);
  tcase_add_test(tc, strcmpSameStringsOtherSymbols);
  tcase_add_test(tc, strcmpDiffStringsOtherSymbols);
  tcase_add_test(tc, strcmpSameStringsJustSpaces);
  tcase_add_test(tc, strcmpEmptyStrings);
  tcase_add_test(tc, strcmpDigits1);
  tcase_add_test(tc, strcmpDigits2);
  tcase_add_test(tc, strcmpSpaces);
  tcase_add_test(tc, strcmpDiffLengthStr1);
  tcase_add_test(tc, strcmpDiffLengthStr2);

  tcase_add_test(tc, memcmpSameStringsSmallLetters);
  tcase_add_test(tc, memcmpSameStringsBigLetters);
  tcase_add_test(tc, memcmpSameStringsDiffLetters);
  tcase_add_test(tc, memcmpSameStringsDigits);
  tcase_add_test(tc, memcmpSameStringsOtherSymbols);
  tcase_add_test(tc, memcmpDiffStringsOtherSymbols);
  tcase_add_test(tc, memcmpSameStringsJustSpaces);
  tcase_add_test(tc, memcmpEmptyStrings);
  tcase_add_test(tc, memcmpDigits1);
  tcase_add_test(tc, memcmpDigits2);
  tcase_add_test(tc, memcmpSpaces);
  tcase_add_test(tc, memcmpDiffLengthStr1);
  tcase_add_test(tc, memcmpDiffLengthStr2);

  tcase_add_test(tc, strncmpSameStringsSmallLetters);
  tcase_add_test(tc, strncmpSameStringsBigLetters);
  tcase_add_test(tc, strncmpSameStringsDiffLetters);
  tcase_add_test(tc, strncmpSameStringsDigits);
  tcase_add_test(tc, strncmpSameStringsOtherSymbols);
  tcase_add_test(tc, strncmpDiffStringsOtherSymbols);
  tcase_add_test(tc, strncmpSameStringsJustSpaces);
  tcase_add_test(tc, strncmpEmptyStrings);
  tcase_add_test(tc, strncmpDigits1);
  tcase_add_test(tc, strncmpDigits2);
  tcase_add_test(tc, strncmpSpaces);
  tcase_add_test(tc, strncmpDiffLengthStr1);
  tcase_add_test(tc, strncmpDiffLengthStr2);

  tcase_add_test(tc, trimSameStrings);
  tcase_add_test(tc, trimEmptyDeleteString);
  tcase_add_test(tc, trimDeleteEdgeSpaces);
  tcase_add_test(tc, trimOtherLetters);
  tcase_add_test(tc, trimSomeLetters);
  tcase_add_test(tc, trimInnerLetters);
  tcase_add_test(tc, trimEmptyStr);

  tcase_add_test(tc, strcatSimple);
  tcase_add_test(tc, strcatAddToEmpty);
  tcase_add_test(tc, strcatBothEmpty);
  tcase_add_test(tc, strcatAddEmpty);
  
  tcase_add_test(tc, strncatSimple1);
  tcase_add_test(tc, strncatSimple2);
  tcase_add_test(tc, strncatSimple3);
  tcase_add_test(tc, strncatAddToEmpty1);
  tcase_add_test(tc, strncatAddToEmpty2);
  tcase_add_test(tc, strncatAddToEmpty3);
  tcase_add_test(tc, strncatBothEmpty1);
  tcase_add_test(tc, strncatBothEmpty2);
  tcase_add_test(tc, strncatAddEmpty1);
  tcase_add_test(tc, strncatAddEmpty2);
  
  tcase_add_test(tc, strspnSearchSomeLetters);
  tcase_add_test(tc, strspnSearchEmpty);
  tcase_add_test(tc, strspnSameStrings);
  tcase_add_test(tc, strspnSearchInEmptyString);
  tcase_add_test(tc, strspnBothEmpty);
  tcase_add_test(tc, strspnSearchOtherChars);
  tcase_add_test(tc, strspnBothStringsOnlySpaces);

  tcase_add_test(tc, strcspnBothStringsOnlySpaces);
  tcase_add_test(tc, strcspnSameStrings);
  tcase_add_test(tc, strcspnDiffStrings);
  tcase_add_test(tc, strcspnBothStringsEmpty);
  tcase_add_test(tc, strcspnSearchInEmpty);
  tcase_add_test(tc, strcspnSameSuffix);

  tcase_add_test(tc, strtokSimple);
  tcase_add_test(tc, strtokEmptyDelim);
  tcase_add_test(tc, strtokSameStrs);
  tcase_add_test(tc, strtokBothEmpty);
  tcase_add_test(tc, strtokEmptyStr);
  tcase_add_test(tc, strtokMatchOnlyLastLetter);
  tcase_add_test(tc, strtokMatchMidAndLastChars);
  tcase_add_test(tc, strtokMatchFromMidToEndChars);

  suite_add_tcase(s, tc);

  return s;
}

// int main() {
//   Suite* s = suite();
//   SRunner* sr = srunner_create(s);

//   srunner_run_all(sr, CK_NORMAL);
  
//   srunner_free(sr);
  
//   return 0;
// }
