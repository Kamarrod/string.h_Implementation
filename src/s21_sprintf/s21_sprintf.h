#ifndef S21STRING
#define S21STRING
#include <stdarg.h>
struct info {
  char fl;
  int width;
  int acc;
  char len;
  char spec;
};

char *itoa(int val, int base);
void init_struct(struct info *mys);
void cpf_width(const char *pF, struct info *mys, va_list input, int * i);
void cpf_acc(const char *pF, struct info *mys, va_list input, int * i);
void check_part_format(const char *pF, struct info *mys, va_list input, int * i);
void ppts_width_fill_nulls(char* num_s, char* str, int col_spaces);
void ppts_width_align_right(char* num_s, char* str, int col_spaces, struct info *mys);
void ppts_width_align_left(char* num_s, char* str, int col_spaces);
void print_part_to_str(char *str, struct info *mys, va_list input);
int s21_sprintf(char* str, const char* format, ...);
#endif