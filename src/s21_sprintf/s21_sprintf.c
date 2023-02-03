#include "s21_sprintf.h"
#include "string.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
//#include <float.h>
#include <math.h>

void init_struct(struct info *mys) {
  mys->fl = '_';
  mys->width = -1;
  mys->acc = -1;
  mys->len = '_';
  mys->spec = '_';
  mys->block_zero = 0;
  mys->was_shift = 0;
}

void ppts_width_fill_nulls(char *num_s, char *str, int col_spaces,
                           int col_zeros, struct info *mys) {
  if (num_s[0] != '-' &&
      num_s[0] != '+') { //есть какая-то ширина и стоит флаг 0

    if (col_zeros > 0) { //если даже стоит фл 0 но есть точность все заполнять
                         //нулями не будем
      for (int i = 0; i < col_spaces; i++)
        strcat(str, " ");
      for (int i = 0; i < col_zeros; i++)
        strcat(str, "0");
    } else {
      for (int i = 0; i < col_spaces; i++)
      if(mys->block_zero==0)
        strcat(str, "0");
    }
  if(mys->block_zero==0)
    strcat(str, num_s);
  } else if (num_s[0] == '-' || num_s[0] == '+') { //сначала знак потом нули
                                                   //потом число
    if (num_s[0] == '-')
      strcat(str, "-");
    else
      strcat(str, "+");

    if (col_zeros > 0) { //если даже стоит фл 0 но есть точность все заполнять
                         //нулями не будем
      for (int i = 0; i < col_spaces; i++)
        strcat(str, " ");
      for (int i = 0; i < col_zeros; i++)
        strcat(str, "0");
    } else {
      for (int i = 0; i < col_spaces; i++)
      if(mys->block_zero==0)
        strcat(str, "0");
    }
  if(mys->block_zero==0)
    strcat(str, &num_s[1]);
  }
}

void ppts_width_align_right_s(struct info *mys, char *s, char *str,
                              int col_spaces) {
  for (int i = 0; i < col_spaces; i++)
    strcat(str, " ");
  if (mys->acc >= 1)
    strncat(str, s, mys->acc);
  else
    strcat(str, s);
}

void ppts_width_align_left_s(struct info *mys, char *s, char *str,
                             int col_spaces) {
  if (mys->acc >= 1)
    strncat(str, s, mys->acc);
  else
    strcat(str, s);
  for (int i = 0; i < col_spaces; i++)
    strcat(str, " ");
}
void ppts_acc_s(struct info *mys, char *s, char *str) {
  strncat(str, s, mys->acc);
}

void ppts_width_s(struct info *mys, char *s, char *str) {
  int col_spaces;
  if (mys->acc >= 1)
    col_spaces = mys->width - mys->acc;
  else
    col_spaces = mys->width - strlen(s);

  if (col_spaces >= 1) {
    if (mys->fl != '-') { //выравнивание правому краю в пределах заданной ширины
      ppts_width_align_right_s(mys, s, str, col_spaces);
    } else if (mys->fl == '-') { //Выравнивание по левому краю в пределах
                                 //заданной ширины
      ppts_width_align_left_s(mys, s, str, col_spaces);
    }
  } else if (mys->acc >= 1) {
    ppts_acc_s(mys, s, str);
  } else {
    strcat(str, s);
  }
}

void ppts_acc_f(struct info *mys, char *num_s, char *str) {
  //учитываем ширину
  
  if(mys->width!=-1){
    
    if(mys->fl=='-')
      strcat(str, num_s);

    for (int i = 0; i < mys->width - strlen(num_s);i++) {
      if(mys->fl=='0')
        strcat(str, "0");
      else
        strcat(str, " ");
    }
  }
  if(mys->fl!='-')
    strcat(str, num_s);
}


char *add_plus_nums(struct info *mys, char *num_s) {
  char *p1 = NULL;
  p1 = malloc((strlen(num_s) + 2) * sizeof(char));
  if (p1) {
    strcpy(p1, "+");
    strcat(p1, num_s);
  }
  return p1;
}

char *add_space_nums(struct info *mys, char *num_s) {
  char *p1 = NULL;
  p1 = malloc((strlen(num_s) + 2) * sizeof(char));
  if (p1) {
    strcpy(p1, " ");
    strcat(p1, num_s);
  }
  return p1;
}

void print_part_to_str(char *str, struct info *mys, va_list input, int* exist_c_null, int j, int* ret_val) {
  //case i d
  long num;
  char *num_s;
  int len_num_s = 0;
  char c;
  char *s = NULL;
  unsigned ui;
  unsigned long uli;
  long double d;
  float f;

  switch (mys->spec) {
  case 'i':
  case 'd':
    if (mys->len == 'l'){
      num = va_arg(input, long);
    } else {
      num = va_arg(input, int);
    }
    num_s = itoa(num, 0);
    if (mys->fl == '+' && num_s[0] != '-') { // флаг+
      num_s = add_plus_nums(mys, num_s); 
    }
    if (mys->fl == ' '&& num_s[0] != '-'){
      num_s = add_space_nums(mys, num_s);
    }
    if(mys->acc == 0 && num == 0)
      mys->block_zero = 1; 
    len_num_s += strlen(num_s);
    if (mys->width != -1) { //ширина / +внутри точность 
      ppts_width_i_d(mys, len_num_s, num_s, str);
    } else if (mys->acc != -1 && mys->block_zero==0) {//не установлена ширина - проверяем сразу точность 
      ppts_acc_i_d(mys, len_num_s, num_s, str);
    } else {
      if(mys->block_zero==0)
        strcat(str, num_s);
      else {
        if (mys->fl == '+')
          strcat(str, "+");
        else if(mys->fl == ' ')
          strcat(str, " ");
      }
    }
    if ((mys->fl == '+'|| mys->fl == ' ')&& num_s[0] != '-'&& num_s!=NULL){
      free(num_s);
    }
    break;

  case 'c':
  case '%':
    c = va_arg(input, int);
    if(c==0)
      *exist_c_null=1;
    ppts_width_c(mys, c, str, j, *exist_c_null);
    if(mys->width>0)
      *ret_val +=mys->width - 1; 
    break;

  case 's':
    s = va_arg(input, char *);
    if (mys->width != -1) {
      ppts_width_s(mys, s, str);
    } else if (mys->acc != -1) {
      ppts_acc_s(mys, s, str);
    } else {
      strcat(str, s);
    }
    break;
  case 'u':
    if(mys->len=='l')
      uli = va_arg(input, unsigned long);
    else 
      uli = va_arg(input, unsigned);
    num_s=__utoa(uli);
    len_num_s += strlen(num_s);
    
    if(mys->acc == 0 && uli == 0)
      mys->block_zero = 1; 
    if (mys->width != -1) {
      ppts_width_i_d(mys, len_num_s, num_s, str);
    } else if (mys->acc != -1 ) {
      ppts_acc_u(mys, len_num_s , num_s, str);
    } else {
        strcat(str, num_s);
    }
    break;
  
  case 'f':
    //printf("PPTS:F:MYSLEN: %c\n", mys->len);
    if(mys->len=='L')
      d = va_arg(input, long double);
    else
      d = va_arg(input, double);

    printf("PPTS:F:MYSACC: %d\n", mys->acc);
    if(mys->acc==0)
      num_s = ftoa(d, 0, mys->fl);
    else if(mys->acc==-1)
      num_s = ftoa(d, 6, mys->fl);
    else
      num_s = ftoa(d, mys->acc, mys->fl);

    len_num_s = strlen(num_s);
    //printf("FUNC:NUMS:%s\n", num_s);
    //printf("FUNC:LEN NUMS:%ld\n", strlen(num_s));
    ppts_acc_f(mys, num_s, str);
    break;
  
  
  default:
    break;
  }
}

int s21_sprintf(char *str, const char *format, ...) {
  struct info mys = {'_', -1, -1, '_', '_', 0, 0};
  va_list(input);
  va_start(input, format);
  int i = 0;
  int j = 0;
  int exist_c_null=0;
  str[0]='\0';
  int ret_val = 0;
  while (format[i] != '\0') {
    if (format[i] == '%') { //здесь смотри как записать в buf то что идет после процента
      i++;
      check_part_format(format, &mys, input, &i);
      print_part_to_str(str, &mys, input, &exist_c_null, j, &ret_val);//пишем форматированный кусок в buf
      j = strlen(str);
    } else {
      if(exist_c_null){//для флага с при char 0
        j++;
        str[j] = format[i];
        exist_c_null=0;
      } 
      else
        str[j] = format[i];
      i++;
      j++;
    }
    ret_val++;
    str[j] = '\0';
  }
  va_end(input);
  if(mys.spec!='c')
    ret_val = strlen(str);
  return ret_val;

}


//%[флаги][ширина][.точность][длина]спецификатор. 
//test 10
// int main() {
//   char str1[200];
//   char str2[200];
//   char *str3 = "%u Test %3.u Test %5.7u TEST %10u %#u %-u %+u %.u % .u";
//   unsigned int val = 0;
//   sprintf(str1, str3, val, val, val, val, val, val, val, val, val);
//   s21_sprintf(str2, str3, val, val, val, val, val, val, val, val, val);
//   printf("MAIN:S21PRINTF:%s\n", str2);
//   printf("MAIN:PRINTF   :%s\n", str1);
//   printf("MAIN:S21PRINTF SIZE:%ld\n", strlen(str2));
//   printf("MAIN:PRINTF   SIZE:%ld\n", strlen(str1));
//   printf("MAIN:STRCMP:%d\n", strcmp(str1, str2));

//   return 0;
// } 
