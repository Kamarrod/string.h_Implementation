
#include "s21_sprintf.h"
#include "string.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

//#include <float.h>
#include <math.h>
// char *itoa(long val, int base) {
//   static char buf[128] = {0};
//   int i = 30;
//   int neg = 0;
//   if (val < 0) {
//     val = -val;
//     neg = 1;
//   }
//   for (; val && i; --i, val /= base)

//     buf[i] = "0123456789abcdef"[val % base];
//   char *ret_val;
//   ret_val = &buf[i + 1];
//   if (neg) {
//     buf[i] = '-';
//     ret_val = &buf[i];
//   }
//   return ret_val;
// }

char *utoa(unsigned long val, int base) {
  static char buf[128] = {0};
  int i = 30;

  for (; val && i; --i, val /= base)

    buf[i] = "0123456789abcdef"[val % base];
  char *ret_val;
  ret_val = &buf[i + 1];
  return ret_val;
}

void reverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}
 
char* itoa(long x, int d) { 
    static char str[1024] = {0};
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }
    while (i < d)
      str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return str;
}

// char* ftoa(long double n, int afterpoint) {
//     static char res [1024];
//     long ipart = (long)n;
//     long double fpart = n - (long double)ipart;


//     printf("FTOA:IPART:%ld\n", ipart);

    
//     strcpy(res, itoa(ipart,0));
//     int i = strlen(res);
    
//     if (afterpoint != 0) {
//         res[i] = '.';
//         //округление
//         printf("FTOA:FPART:DEC:LF:%.99Lf\n", fpart);
//         fpart = fpart * pow(10, afterpoint);
//         //fpart = fpart * pow(10, afterpoint+1);

        
//         strcat(res, itoa((long)fpart, afterpoint));
//         printf("FTOA:FPART:DEC:LD:%ld\n", (long)fpart);
//         printf("FTOA:FPART:STR:%s\n", itoa((long)fpart, afterpoint));
//     }
//     return res;
// }


char* ftoa(long double n, int afterpoint, char c) {
    static char res [1024];
    if(n<0) {
      n=-n;
      strcpy(res, "-");
    } else {
      if(c=='+')
        strcpy(res, "+");
      else if(c==' ')
        strcpy(res, " ");
    }

    long ipart = (long)n;
    long double fpart = n - (long double)ipart;    
    //printf("FTOA:IPART:%ld\n", ipart);
    strcat(res, itoa(ipart,0));
    int i = strlen(res);
    
    if (afterpoint != 0) {
        res[i] = '.';
        //округление
        //printf("FTOA:FPART:DEC:LF:%.99Lf\n", fpart);
        fpart = roundl(fpart * pow(10, afterpoint));
        //printf("FTOA:FPART:DEC:LF:%Lf\n", roundl(fpart));
        strcat(res, itoa((long)fpart, afterpoint));
        //printf("FTOA:FPART:DEC:LD:%ld\n", (long)fpart);
        //printf("FTOA:FPART:STR:%s\n", itoa((long)fpart, afterpoint));
    }
    return res;
}

void init_struct(struct info *mys) {
  mys->fl = '_';
  mys->width = -1;
  mys->acc = -1;
  mys->len = '_';
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

void ppts_width_fill_nulls(char *num_s, char *str, int col_spaces,
                           int col_zeros) {
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
        strcat(str, "0");
    }
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
        strcat(str, "0");
    }

    strcat(str, &num_s[1]);
  }
}

void ppts_width_align_right_i_d(char *num_s, char *str, int col_spaces,
                                int col_zeros, struct info *mys) {
  if (mys->fl != '0') {

    if (num_s[0] != '-' && num_s[0] != '+') {
      for (int i = 0; i < col_spaces; i++)
        strcat(str, " ");
      for (int i = 0; i < col_zeros; i++)
        strcat(str, "0");
      strcat(str, num_s);
    } else if (num_s[0] == '-' || num_s[0] == '+') {
      for (int i = 0; i < col_spaces; i++)
        strcat(str, " ");

      if (num_s[0] == '-')
        strcat(str, "-");
      else
        strcat(str, "+");

      for (int i = 0; i < col_zeros; i++)
        strcat(str, "0");
      strcat(str, &num_s[1]);
    }
  } else if (mys->fl == '0') { //Заполняет число слева нулями (0) вместо
                               //пробелов, где указан спецификатор ширины
    ppts_width_fill_nulls(num_s, str, col_spaces, col_zeros);
  }
}

void ppts_width_align_left_i_d(char *num_s, char *str, int col_spaces,
                               int col_zeros) {

  if (num_s[0] != '-' && num_s[0] != '+') {
    for (int i = 0; i < col_zeros; i++)
      strcat(str, "0");
    strcat(str, num_s);
    for (int i = 0; i < col_spaces; i++)
      strcat(str, " ");
  } else if (num_s[0] == '-' || num_s[0] == '+') {
    if (num_s[0] == '-')
      strcat(str, "-");
    else
      strcat(str, "+");

    for (int i = 0; i < col_zeros; i++)
      strcat(str, "0");
    strcat(str, &num_s[1]);
    for (int i = 0; i < col_spaces; i++)
      strcat(str, " ");
  }
}
void ppts_width_i_d(struct info *mys, int len_num_s, char *num_s, char *str) {
  int col_spaces = 0;
  int col_zeros = 0;
  if (mys->acc == -1)
    col_spaces = mys->width - len_num_s;
  else {
    col_zeros = mys->acc - len_num_s;
    col_spaces = mys->width - mys->acc;
  }

  if (col_spaces >= 1 || col_zeros >= 1) {
    if (mys->fl != '-') { //выравнивание правому краю в пределах заданной ширины
      ppts_width_align_right_i_d(num_s, str, col_spaces, col_zeros, mys);
    } else if (mys->fl == '-') { //Выравнивание по левому краю в пределах
                                 //заданной ширины
      ppts_width_align_left_i_d(num_s, str, col_spaces, col_zeros);
    }
  } else {
    strcat(str, num_s);
  }
}

void ppts_acc_i_d(struct info *mys, int len_num_s, char *num_s, char *str) {
  int col_zeros = mys->acc - len_num_s;
  if (col_zeros >= 1) {
    if (num_s[0] == '+')
      strcat(str, "+");
    else if (num_s[0] == '-')
      strcat(str, "-");
    else if (mys->fl == ' ')
      strcat(str, " ");

    for (int i = 0; i < col_zeros; i++)
      strcat(str, "0");

    if (num_s[0] == '+' || num_s[0] == '-') {
      strcat(str, &num_s[1]);
    } else {
      strcat(str, num_s);
    }
  } else {
    strcat(str, num_s);
  }
}

void ppts_width_align_left_c(char c, char *str, int col_spaces) {
  strncat(str, &c, 1);
  for (int i = 0; i < col_spaces; i++)
    strcat(str, " ");
}

void ppts_width_align_right_c(char c, char *str, int col_spaces) {
  for (int i = 0; i < col_spaces; i++)
    strcat(str, " ");
  strncat(str, &c, 1);
}

void ppts_width_c(struct info *mys, char c, char *str) {
  int col_spaces = mys->width - 1;

  if (col_spaces >= 1) {
    if (mys->fl != '-') { //выравнивание правому краю в пределах заданной ширины
      ppts_width_align_right_c(c, str, col_spaces);
    } else if (mys->fl == '-') { //Выравнивание по левому краю в пределах
                                 //заданной ширины
      ppts_width_align_left_c(c, str, col_spaces);
    }
  } else {
    strncat(str, &c, 1);
  }
}

void ppts_acc_s(struct info *mys, char *s, char *str) {
  strncat(str, s, mys->acc);
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

char *add_plus_nums(struct info *mys, char *num_s) {
  char *p1 = NULL;
  p1 = malloc((strlen(num_s) + 2) * sizeof(char));
  if (p1) {
    strcpy(p1, "+");
    strcat(p1, num_s);
  }
  return p1;
}

void ppts_acc_u(struct info *mys, int len_num_s, char *num_s, char *str) {
  int col_zeros = mys->acc - len_num_s;
  if (col_zeros >= 1) {
    for (int i = 0; i < col_zeros; i++)
      strcat(str, "0");
      strcat(str, num_s);
  } else {
    strcat(str, num_s);
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



void print_part_to_str(char *str, struct info *mys, va_list input) {
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
    if (mys->len == 'l')
      num = va_arg(input, long);
    else
      num = va_arg(input, int);
    num_s = itoa(num, 0);

    if (mys->fl == '+' && num_s[0] != '-') {
      num_s = add_plus_nums(mys, num_s); //проверит флаг и добавит + если нужно
      if (mys->len == 'l')
        len_num_s = -1;
    }
    len_num_s += strlen(num_s);
    // printf("FUNC:NUM:%ld\n", num);
    // printf("FUNC:NUMS:%s\n", num_s);
    // printf("FUNC:LEN NUMS:%ld\n", strlen(num_s));
    // printf("FUNC:mys->width:%d\n", mys->width);
    if (mys->width != -1) { //ширина для числа
      ppts_width_i_d(mys, len_num_s, num_s, str);
    } else if (mys->acc != -1) {
      ppts_acc_i_d(mys, len_num_s, num_s, str);
    } else {
      strcat(str, num_s);
    }
    if (mys->fl == '+')
      free(num_s);
    break;

  case 'c':
  case '%':
    c = va_arg(input, int);
    ppts_width_c(mys, c, str);
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
    if(mys->len=='l'){
      uli = va_arg(input, unsigned long);
      num_s = utoa(uli, 10);
    } else {
      ui = va_arg(input, unsigned);
      num_s = utoa(ui, 10);
    }
    len_num_s += strlen(num_s);

    if (mys->width != -1) {
      ppts_width_i_d(mys, len_num_s, num_s, str);
    } else if (mys->acc != -1) {
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

    //printf("PPTS:F:MYSACC: %d\n", mys->acc);
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
  struct info mys = {'_', -1, -1, '_', '_'};
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
  // printf("FUNC:STRLEN:%ld\n", strlen(str));
  return strlen(str);
}

/*
format −  это С-строка, содержащая один или несколько следующих элементов:
пробельный символ, непробельный символ и спецификаторы формата.
Спецификатор формата для печатающих функций следует прототипу:
%[флаги][ширина][.точность][длина]спецификатор. Спецификатор формата для
сканирующих функций следует прототипу: %[*][ширина][длина]спецификатор.

*/

int main() {
  char str1[256]="";
  char str2[256];
  //   char *format = "% f";
  //   float val = 0;
  // s21_sprintf(str1, format, val);
  // sprintf(str2, format, val);
  
  char *format = "% .0f %.lf %Lf %f %lf %Lf";
    float val = 0;
    double val1 = 0;
    long double val2 = 3515315.153151;
    float val3 = 5.5;
    double val4 = 9851.51351;
    long double val5 = 95919539159.53151351131;

        s21_sprintf(str1, format, val, val1, val2, val3, val4, val5),
        sprintf(str2, format, val, val1, val2, val3, val4, val5);

  
  
  printf("MAIN:S21PRINTF:%s\n", str1);
  printf("MAIN:PRINTF   :%s\n", str2);
  //printf("MAIN:s21 STRLEN:%ld\n", strlen(str1));
  //printf("MAIN:STRLEN:%ld\n", strlen(str2));
  
  return 0;
}
