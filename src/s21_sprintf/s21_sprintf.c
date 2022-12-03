
#include "s21_sprintf.h"
#include "string.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

char *itoa(int val, int base) {
  static char buf[32] = {0};
  int i = 30;
  int neg = 0;
  if (val < 0) {
    val = -val;
    neg = 1;
  }
  for (; val && i; --i, val /= base)

    buf[i] = "0123456789abcdef"[val % base];
  char *ret_val;
  ret_val = &buf[i + 1];
  if (neg) {
    buf[i] = '-';
    ret_val = &buf[i];
  }
  return ret_val;
}

void init_struct(struct info *mys) {
  mys->fl = '_';
  mys->width = -1;
  mys->acc = -1;
  mys->len = 'L';
  mys->spec = '_';
}

void cpf_width(const char *pF, struct info *mys, va_list input, int *i) {
  mys->width = 0;
  if (pF[*i] != '*') {
    char num[256] = "";
    while (strcspn(&pF[*i], "0123456789") == 0) {
      char buf[3];
      buf[0] = pF[*i];
      buf[1] = '\0';
      strcat(num, buf);
      (*i)++;
    }
    strcat(num, "\0");
    mys->width += atoi(num);
  } else if (pF[*i] == '*') {
    mys->width = va_arg(input, int);
    (*i)++;
  }
}
void cpf_acc(const char *pF, struct info *mys, va_list input, int *i) {
  mys->acc = 0;
  char num[256] = "";
  (*i)++;
  if (pF[*i] != '*') {
    while (strcspn(&pF[*i], "0123456789") == 0) {
      char buf[3];
      buf[0] = pF[*i];
      buf[1] = '\0';
      strcat(num, buf);
      (*i)++;
    }
    strcat(num, "\0");
    if (strlen(num) != 0)
      mys->acc += atoi(num);
  } else if (pF[*i] == '*') {
    mys->acc = va_arg(input, int);
    (*i)++;
  }
}

void check_part_format(const char *pF, struct info *mys, va_list input,
                       int *i) {
  init_struct(mys);
  int was_spec = 0;
  // printf("&PF[i]:%s\n", &pF[*i]);
  while (pF[*i] != '\0' && was_spec == 0) {
    if (strcspn(&pF[*i], "-+ #0") == 0) {
      mys->fl = pF[*i];
      (*i)++;
    } else if (strcspn(&pF[*i], "0123456789*") == 0) {
      cpf_width(pF, mys, input, i);
    } else if (pF[*i] == '.') {
      cpf_acc(pF, mys, input, i);
    } else if (strcspn(&pF[*i], "lhL") == 0) {
      mys->len = pF[*i];
      (*i)++;
    } else if (strcspn(&pF[*i], "cdeEfgGosuxXpni") == 0) {
      mys->spec = pF[*i];
      was_spec = 1;
      (*i)++;
    }
  }
}

void ppts_width_fill_nulls(char *num_s, char *str, int col_spaces, int col_zeros) {
  if (num_s[0] != '-' &&
      num_s[0] != '+') { //есть какая-то ширина и стоит флаг 0
    
    if(col_zeros >0) { //если даже стоит фл 0 но есть точность все заполнять нулями не будем
      for (int i = 0; i < col_spaces; i++)
        strcat(str, " ");
      for (int i = 0; i <col_zeros; i++)
        strcat(str, "0");
    } else {
      for (int i = 0; i < col_spaces; i++)
        strcat(str, "0");
    }
    strcat(str, num_s);
  } else if (num_s[0] == '-' ||
             num_s[0] == '+') { //сначала знак потом нули
                                //потом число
    if (num_s[0] == '-')
      strcat(str, "-");
    else
      strcat(str, "+");





    if(col_zeros >0) { //если даже стоит фл 0 но есть точность все заполнять нулями не будем
      for (int i = 0; i < col_spaces; i++)
        strcat(str, " ");
      for (int i = 0; i <col_zeros; i++)
        strcat(str, "0");
    } else {
      for (int i = 0; i < col_spaces; i++)
        strcat(str, "0");
    }
    
    
    strcat(str, &num_s[1]);
  }
}

void ppts_width_align_right(char *num_s, char *str, int col_spaces,
                            int col_zeros, struct info *mys) {
  if (mys->fl != '0') {
    for (int i = 0; i < col_spaces; i++)
      strcat(str, " ");
    for (int i = 0; i < col_zeros; i++)
      strcat(str, "0");
    strcat(str, num_s);
  } else if (mys->fl ==
             '0') { //Заполняет число слева нулями (0) вместо пробелов,
                    //где указан спецификатор ширины
    ppts_width_fill_nulls(num_s, str, col_spaces, col_zeros);
  }
}

void ppts_width_align_left(char *num_s, char *str, int col_spaces, int col_zeros) {
  for (int i = 0; i < col_zeros; i++)
    strcat(str, "0");
  strcat(str, num_s);
  for (int i = 0; i < col_spaces; i++)
    strcat(str, " ");
}

void print_part_to_str(char *str, struct info *mys, va_list input) {
  int num;
  char *num_s;
  int len_num_s;
  switch (mys->spec) {
  case 'i': case 'd':
    num = va_arg(input, int);
    // printf("%d\n", num);
    //проверить нужно ли чистить память после itoa
    num_s = itoa(num, 10);
    if (mys->fl == '+') {
      if (num_s[0]!='-') {
        char *p1 = malloc((strlen(num_s)+1)*sizeof(char));
        strcpy(p1, "+");
        strcat(p1, num_s);
        num_s = p1;
      }

    }
    len_num_s = strlen(num_s);

    // printf("FUNC:NUMS:%s\n", num_s);
    // printf("FUNC:LEN NUMS:%ld\n", strlen(num_s));
    // printf("FUNC:mys->width:%d\n", mys->width);
    if (mys->width != -1) { //ширина для числа
      int col_spaces = 0;
      int col_zeros = 0;
      if(mys->acc == -1)
        col_spaces = mys->width - len_num_s;
      else {
        col_zeros = mys->acc - len_num_s;
        col_spaces = mys->width - mys->acc;
      }

      if (col_spaces >= 1 || col_zeros >=1) {
        if (mys->fl !=
            '-') { //выравнивание правому краю в пределах заданной ширины
          ppts_width_align_right(num_s, str, col_spaces,col_zeros, mys);
        } else if (mys->fl == '-') { //Выравнивание по левому краю в пределах
                                     //заданной ширины
          ppts_width_align_left(num_s, str, col_spaces, col_zeros);
        }
      } else {
        strcat(str, num_s);
      }
    } else if (mys->acc != -1) {
      int col_zeros = mys->acc - len_num_s;
      if (col_zeros >= 1) {
        if (num_s[0] == '+')
          strcat(str, "+");
        else if (num_s[0] == '-')
          strcat(str, "-");

        for (int i = 0; i < col_zeros; i++)
          strcat(str, "0");

        if (num_s[0] == '+' || num_s[0] == '-') {
          strcat(str, &num_s[1]);
        } else {
          strcat(str, num_s);
        }
      }
    } else {
      strcat(str, num_s);
    }
    if (mys->fl == '+') 
      free(num_s);
    break;

  default:
    break;
  }
}

int s21_sprintf(char *str, const char *format, ...) {
  struct info mys = {'_', -1, -1, 'L', '_'};
  va_list(input);
  va_start(input, format);
  int i = 0;
  int j = 0;
  while (format[i] != '\0') {
    if (format[i] == '%') {
      //здесь смотри как записать в buf то что идет после процента
      i++;
      check_part_format(format, &mys, input, &i);
      //пишем форматированный кусок в buf
      print_part_to_str(str, &mys, input);
      j = strlen(str);
    } else {
      str[j] = format[i];
      i++;
      j++;
    }
    str[j] = '\0';
  }

  va_end(input);
  //printf("FUNC:STRLEN:%ld\n", strlen(str));
  return strlen(str);
}

/*
format −  это С-строка, содержащая один или несколько следующих элементов:
пробельный символ, непробельный символ и спецификаторы формата.
Спецификатор формата для печатающих функций следует прототипу:
%[флаги][ширина][.точность][длина]спецификатор. Спецификатор формата для
сканирующих функций следует прототипу: %[*][ширина][длина]спецификатор.

*/
// int main() {
//   char str1[256];
//   char str2[256];
//   //const char *format = "%0.*i %d %.*i %013d %d";
//   const char *format = "%012i";
  
//   int val = 69;
//   s21_sprintf(str1, format , val);
//   sprintf(str2, format , val);

//   printf("MAIN:S21 sPRINTF:%s\n", str1);
//   printf("MAIN:SPRINTF:%s\n", str2);
//   printf("MAIN:s21 STRLEN:%ld\n", strlen(str1));
//   printf("MAIN:STRLEN:%ld\n", strlen(str2));
//   return 0;
// }