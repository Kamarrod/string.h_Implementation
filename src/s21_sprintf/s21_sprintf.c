#include "s21_sprintf.h"
#include "string.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
//#include <float.h>
#include <math.h>









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
  int neg = 0;
  int long_min=0;
  if (x < 0) {
    //костыль для min_long
    if(x==LONG_MIN){
      x=LONG_MAX;
      long_min=1;
    } else {
      x = -x;
    }
    neg = 1;
  }


  static char str[1024] = {0};
  
  //тк статик чтобы убирать мусор между итерациями
  for (int k = 0; k <= 1024; k++)
      str[k] = '\0';
  int i = 0;
  
    if(x==0)
      str[i] = '0';
    else {
      while (x) {
          str[i++] = (x % 10) + '0';
          x = x / 10;
      }
      while (i < d)
        str[i++] = '0';

      reverse(str, i);
    }
    str[i+1] = '\0';
    

    if(neg){
      for (int j=i+1; j>=0; j--)
        str[j] = str[j-1];
      str[0]='-';

      if(long_min){////костыль для min_long продолжение
        str[i] +=1;
      } 
      str[i+2] = '\0';
    }
    return str;
}

char* ftoa(long double n, int afterpoint, char c) {
    static char res [1024]={0};
    for (int k = 0; k <= 1024; k++)
      res[k] = '\0';

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
        printf("FTOA:FPART:DEC:LF:%.16Lf\n", fpart);
        fpart = roundl(fpart * pow(10, afterpoint));
        //fpart = fpart * pow(10, afterpoint);
        printf("FTOA:FPART:DEC:LF:%Lf\n", fpart);
        strcat(res, itoa((long)fpart, afterpoint));
        printf("FTOA:FPART:DEC:LD:%ld\n", (long)fpart);
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

    //проверки флагa
    if (mys->fl == '+' && num_s[0] != '-') { // флаг+
      num_s = add_plus_nums(mys, num_s); 
      // if (mys->len == 'l')
      //   len_num_s = -1;
    }
    if (mys->fl == ' '&& num_s[0] != '-'){
      num_s = add_space_nums(mys, num_s);
    }
    //иницилизируем поле структуры block_zero
    if(mys->acc == 0 && num == 0)
      mys->block_zero = 1; 
    
    len_num_s += strlen(num_s);
    // printf("FUNC:NUM:%ld\n", num);
    // printf("FUNC:NUMS:%s\n", num_s);
    // printf("FUNC:LEN NUMS:%ld\n", strlen(num_s));
    //printf("FUNC:mys->width:%d\n", mys->width);
   
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
     // printf("PPTS: FREED\n");
     // printf("PPTS: LEN %d\n", strlen(num_s));
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

//test12

// int main() {
//   int ret_orig;
//   char str1[100];
//   char str2[100];
//   char *str3 = "%c Test %c Test %c Test %c Test %c";
// ret_orig= sprintf(str1, str3, '\n', '\0', '\0', '\0', 'c');
// s21_sprintf(str2, str3, '\n', '\0', '\0', '\0', 'c');
//   printf("MAIN:S21PRINTF:%s\n", str2);
//   printf("MAIN:PRINTF   :%s\n", str1);
//   printf("MAIN:S21PRINTF SIZE:%ld\n", strlen(str2));
//   printf("MAIN:PRINTF   SIZE:%ld\n", strlen(str1));
//   printf("MAIN:STRCMP:%d\n", strcmp(str1, str2));

//   for(int i=0; i < strlen(str1); i++)
//     printf("STR1[%d]= %c\n", i, str1[i]);
//   for(int i=0; i < strlen(str2); i++)
//     printf("STR2[%d]= %c\n", i, str2[i]);
  
//   printf("ret_orig = %d\n", ret_orig);

//   return 0;
// } 


// int main() {
//   char str1[100];
//   char str2[100];
//   char *str3 = "%05c Test % 5c Test %lc Test";
//   int a = 70;
//   unsigned long int b = 70;
// sprintf(str1, str3, a, a, b);
// s21_sprintf(str2, str3, a, a, b);


//   printf("MAIN:S21PRINTF:%s\n", str2);
//   printf("MAIN:PRINTF   :%s\n", str1);
//   printf("MAIN:S21PRINTF SIZE:%ld\n", strlen(str2));
//   printf("MAIN:PRINTF   SIZE:%ld\n", strlen(str1));
//   printf("MAIN:STRCMP:%d\n", strcmp(str1, str2));

//   return 0;
// } 