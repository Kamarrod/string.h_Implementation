#ifndef S21_STRING
#define S21_STRING
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#define s21_size_t unsigned long long
#define s21_NULL (void *)0
struct info {
  char fl;

  int width;
  int acc;
  char len;
  char spec;
  int block_zero;
  int was_shift;
  int was_plus;
  int was_space;
  int was_sharp;
};

// i d
void ppts_width_align_right_i_d(char *num_s, char *str, int col_spaces,
                                int col_zeros, struct info *mys);
void ppts_width_align_left_i_d(char *num_s, char *str, int col_spaces,
                               int col_zeros, struct info *mys);
void ppts_width_i_d(struct info *mys, int len_num_s, char *num_s, char *str);
void ppts_acc_i_d(struct info *mys, int len_num_s, char *num_s, char *str);
void ppts_width_fill_nulls(char *num_s, char *str, int col_spaces,
                           int col_zeros, struct info *mys);

// c
void ppts_width_align_left_c(char c, char *str, int col_spaces);
void ppts_width_align_right_c(char c, char *str, int col_spaces,
                              struct info *mys);
void ppts_width_c(struct info *mys, char c, char *str, int j);
// u
void ppts_acc_u(struct info *mys, int len_num_s, char *num_s, char *str);
// typecasting
void reverse(char *str, int len);
char *itoa(long x, int d);
char *ftoa(long double n, int afterpoint, char c);
char *utoa(unsigned long value);
char *ulltoa(s21_size_t x, int d);
int s21_atoi(char *str);
char *ulltoa(s21_size_t x, int d);

// s
void ppts_width_align_right_s(struct info *mys, char *s, char *str,
                              int col_spaces);
void ppts_width_align_left_s(struct info *mys, char *s, char *str,
                             int col_spaces);
void ppts_width_s(struct info *mys, char *s, char *str);
void ppts_acc_s(struct info *mys, char *s, char *str);
// f
void ppts_f(struct info *mys, char *num_s, char *str);

// parser.h
void cpf_width(const char *pF, struct info *mys, va_list input, int *i);
void cpf_acc(const char *pF, struct info *mys, va_list input, int *i);
void check_part_format(const char *pF, struct info *mys, va_list input, int *i);
void init_struct(struct info *mys);
int s21_sprintf(char *str, const char *format, ...);

char *s21_strchr(const char *str, int c);
char *s21_strcpy(char *dest, const char *src);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
void *s21_memchr(const void *str, int c, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
void *s21_to_upper(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);

s21_size_t s21_strlen(const char *str);                             // ++
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);   // ++
int s21_strcmp(const char *str1, const char *str2);                 // ++
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);  // ++
char *s21_strtok(char *str, const char *delim);
char *s21_strerror(int errnum);                                // ++
char *s21_strcat(char *dest, const char *src);                 // ++
char *s21_strncat(char *dest, const char *src, s21_size_t n);  // ++
s21_size_t s21_strspn(const char *str1, const char *str2);     // ++
s21_size_t s21_strcspn(const char *str1, const char *str2);    // ++

void *s21_to_lower(const char *str);                      // ++
void *s21_trim(const char *src, const char *trim_chars);  // ++

int contains(char c, const char *str);
void refreshUnknownError(int errnum);
char *getNumberFromInt(int number);
#endif  /////S21_STRING