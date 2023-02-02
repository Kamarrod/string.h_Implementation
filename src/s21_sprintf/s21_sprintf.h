#ifndef S21SPRINTF
#define S21SPRINTF
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
struct info {
  char fl;
  int width;
  int acc;
  char len;
  char spec;
  int block_zero;
  int was_shift;
};

//i d
void ppts_width_align_right_i_d(char *num_s, char *str, int col_spaces,
                                int col_zeros, struct info *mys);
void ppts_width_align_left_i_d(char *num_s, char *str, int col_spaces,
                               int col_zeros, struct info *mys);
void ppts_width_i_d(struct info *mys, int len_num_s, char *num_s, char *str);
void ppts_acc_i_d(struct info *mys, int len_num_s, char *num_s, char *str);
//c
void ppts_width_align_left_c(char c, char *str, int col_spaces, struct info *mys);
void ppts_width_align_right_c(char c, char *str, int col_spaces, struct info *mys);
void ppts_width_c(struct info *mys, char c, char *str);


//s
void ppts_acc_s(struct info *mys, char *s, char *str);

void init_struct(struct info *mys);
//parser.h
void cpf_width(const char *pF, struct info *mys, va_list input, int * i);
void cpf_acc(const char *pF, struct info *mys, va_list input, int * i);
void check_part_format(const char *pF, struct info *mys, va_list input, int * i);

void ppts_width_fill_nulls(char *num_s, char *str, int col_spaces, int col_zeros, struct info *mys);

void print_part_to_str(char *str, struct info *mys, va_list input, int* exist_c_null) ;
int s21_sprintf(char* str, const char* format, ...);
#endif