#ifndef S21SPRINTF
#define S21SPRINTF
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void ppts_width_align_left_c(char c, char *str, int col_spaces,
                             struct info *mys, int j);
void ppts_width_align_right_c(char c, char *str, int col_spaces,
                              struct info *mys, int j);
void ppts_width_c(struct info *mys, char c, char *str, int j, int exist_c_null);
// u
void ppts_acc_u(struct info *mys, int len_num_s, char *num_s, char *str);
// typecasting
void reverse(char *str, int len);
char *itoa(long x, int d);
char *ftoa(long double n, int afterpoint, char c);
char *utoa(unsigned long value);
char *ulltoa(unsigned long long x, int d);

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

// void print_part_to_str(char *str, struct info *mys, va_list input, int*
// exist_c_null, int j, int* ret_val);
int s21_sprintf(char *str, const char *format, ...);
#endif