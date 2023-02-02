#include "s21_sprintf.h"
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
      
      if(mys->fl=='-')//для 19 теста
        mys->was_shift=1;
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
/*


1
если есть знак нет ширины
сдвиг влево- пробел
---------------
важен только -

2
если есть знак ширина
сдвиг влево- пробел 
---------------
важен только -

3
если нет знака ширина
сдвиг влево- пробел 
---------------
важны оба

4
если нет знака нет ширины
сдвиг влево- пробел 
---------------
важны оба флага


*/