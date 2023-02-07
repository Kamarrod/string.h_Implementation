#include "jer_sprintf.h"

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "string.h"

void init_struct(struct info *mys) {
  mys->fl = '_';
  mys->width = -1;
  mys->acc = -1;
  mys->len = '_';
  mys->spec = '_';
  mys->block_zero = 0;
  mys->was_shift = 0;
  mys->was_plus = 0;
  mys->was_space = 0;
  mys->was_sharp = 0;
}

char *add_plus_nums(char *num_s) {
  char *p1 = NULL;
  p1 = malloc((strlen(num_s) + 2) * sizeof(char));
  if (p1) {
    strcpy(p1, "+");
    strcat(p1, num_s);
  }
  return p1;
}

char *add_space_nums(char *num_s) {
  char *p1 = NULL;
  p1 = malloc((strlen(num_s) + 2) * sizeof(char));
  if (p1) {
    strcpy(p1, " ");
    strcat(p1, num_s);
  }
  return p1;
}

void ppts_case_id(struct info *mys, va_list input, char *str) {
  long num;
  char *num_s;

  int len_num_s = 0;
  if (mys->len == 'l') {
    num = va_arg(input, long);
  } else {
    num = va_arg(input, int);
  }
  num_s = itoa(num, 0);
  if (mys->fl == '+' && num_s[0] != '-') {  // флаг+
    num_s = add_plus_nums(num_s);
  }
  if (mys->fl == ' ' && num_s[0] != '-') {
    num_s = add_space_nums(num_s);
  }
  if (mys->acc == 0 && num == 0) mys->block_zero = 1;
  len_num_s += strlen(num_s);
  if (mys->width != -1) {  //ширина / +внутри точность
    ppts_width_i_d(mys, len_num_s, num_s, str);
  } else if (mys->acc != -1 &&
             mys->block_zero ==
                 0) {  //не установлена ширина - проверяем сразу точность
    ppts_acc_i_d(mys, len_num_s, num_s, str);
  } else {
    if (mys->block_zero == 0)
      strcat(str, num_s);
    else {
      if (mys->fl == '+')
        strcat(str, "+");
      else if (mys->fl == ' ')
        strcat(str, " ");
    }
  }
  if ((mys->fl == '+' || mys->fl == ' ') && num_s[0] != '-' && num_s != NULL) {
    free(num_s);
  }
}

void ppts_case_c(int *exist_c_null, int *ret_val, int j, char *str,
                 struct info *mys, va_list input) {
  char c;
  c = va_arg(input, int);
  if (c == 0) *exist_c_null = 1;
  ppts_width_c(mys, c, str, j);
  if (mys->width > 0) *ret_val += mys->width - 1;
}

void ppts_case_s(struct info *mys, va_list input, char *str) {
  char *s = NULL;
  s = va_arg(input, char *);
  char *nullstr = "(null)";
  if (s == NULL) s = nullstr;

  if (mys->width != -1) {
    ppts_width_s(mys, s, str);
  } else if (mys->acc != -1) {
    ppts_acc_s(mys, s, str);
  } else {
    strcat(str, s);
  }
}

void ppts_case_u(struct info *mys, va_list input, char *str) {
  unsigned long uli;
  int len_num_s = 0;
  char *num_s;
  if (mys->len == 'l')
    uli = va_arg(input, unsigned long);
  else
    uli = va_arg(input, unsigned);
  num_s = utoa(uli);
  len_num_s += strlen(num_s);

  if (mys->acc == 0 && uli == 0) mys->block_zero = 1;
  if (mys->width != -1) {
    ppts_width_i_d(mys, len_num_s, num_s, str);
  } else if (mys->acc != -1) {
    ppts_acc_u(mys, len_num_s, num_s, str);
  } else {
    strcat(str, num_s);
  }
}

void ppts_case_f(struct info *mys, va_list input, char *str) {
  long double d;
  char *num_s;

  if (mys->len == 'L')
    d = va_arg(input, long double);
  else
    d = va_arg(input, double);

  char c='_';
  if (mys->was_space || mys->fl == ' ') c = ' ';
  if (mys->was_plus || mys->fl == '+') c = '+';
  if (mys->acc == -1)
    num_s = ftoa(d, 6, c);
  else
    num_s = ftoa(d, mys->acc, c);

  if (mys->acc == 0 && (mys->was_sharp || mys->fl == '#')){
    //  num_s = (char *) realloc(num_s, strlen(num_s)+2);
    //  if(num_s)
    //   strcat(num_s, ".");
      void * tmp =(char *) realloc(num_s, strlen(num_s)+2);
      if (NULL != tmp){
        num_s = tmp;
        strcat(num_s, ".");
      }
  }
  ppts_f(mys, num_s, str);
  if (num_s) free(num_s);
}
void print_part_to_str(char *str, struct info *mys, va_list input,
                       int *exist_c_null, int j, int *ret_val) {
  switch (mys->spec) {
    case 'i':
    case 'd':
      ppts_case_id(mys, input, str);
      break;
    case 'c':
      ppts_case_c(exist_c_null, ret_val, j, str, mys, input);
      break;
    case '%':
      ppts_width_c(mys, '%', str, j);
      if (mys->width > 0) *ret_val += mys->width - 1;
      break;
    case 's':
      ppts_case_s(mys, input, str);
      break;
    case 'u':
      ppts_case_u(mys, input, str);
      break;
    case 'f':
      ppts_case_f(mys, input, str);
      break;
    // default:
    //   break;
  }
}

int s21_sprintf(char *str, const char *format, ...) {
  struct info mys = {'_', -1, -1, '_', '_', 0, 0, 0, 0, 0};
  va_list(input);
  va_start(input, format);
  int i = 0;
  int j = 0;
  int exist_c_null = 0;
  str[0] = '\0';
  int ret_val = 0;
  while (format[i] != '\0') {
    if (format[i] ==
        '%') {  //здесь смотри как записать в buf то что идет после процента
      i++;
      check_part_format(format, &mys, input, &i);
      print_part_to_str(str, &mys, input, &exist_c_null, j,
                        &ret_val);  //пишем форматированный кусок в buf
      j = strlen(str);
    } else {
      if (exist_c_null) {  //для флага с при char 0
        j++;
        str[j] = format[i];
        exist_c_null = 0;
      } else
        str[j] = format[i];
      i++;
      j++;
    }
    ret_val++;
    str[j] = '\0';
  }
  va_end(input);
  if (mys.spec != 'c') ret_val = strlen(str);
  return ret_val;
}
