#include "s21_string.h"
void cpf_width(const char *pF, struct info *mys, va_list input, int *i) {
  mys->width = 0;
  if (pF[*i] != '*') {
    char num[256] = "";
    while (s21_strcspn(&pF[*i], "0123456789") == 0) {
      char buf[3];
      buf[0] = pF[*i];
      buf[1] = '\0';
      s21_strcat(num, buf);
      (*i)++;
    }
    s21_strcat(num, "\0");
    mys->width += s21_atoi(num);
  } else {
    mys->width = va_arg(input, int);
    (*i)++;
  }
}

void cpf_acc(const char *pF, struct info *mys, va_list input, int *i) {
  mys->acc = 0;
  (*i)++;
  if (pF[*i] != '*') {
    char num[256] = "";
    while (s21_strcspn(&pF[*i], "0123456789") == 0) {
      char buf[3];
      buf[0] = pF[*i];
      buf[1] = '\0';
      s21_strcat(num, buf);
      (*i)++;
    }
    s21_strcat(num, "\0");
    if (s21_strlen(num) != 0) mys->acc += s21_atoi(num);
  } else {
    mys->acc = va_arg(input, int);
    (*i)++;
  }
}

void check_part_format(const char *pF, struct info *mys, va_list input,
                       int *i) {
  init_struct(mys);
  int was_spec = 0;
  while (pF[*i] != '\0' && was_spec == 0) {
    if (s21_strcspn(&pF[*i], "-+ #0") == 0) {
      if (mys->fl == '-') mys->was_shift = 1;
      if (mys->fl == '+') mys->was_plus = 1;
      if (mys->fl == ' ') mys->was_space = 1;
      if (mys->fl == '#') mys->was_sharp = 1;
      mys->fl = pF[*i];
      (*i)++;
    } else if (s21_strcspn(&pF[*i], "0123456789*") == 0) {
      cpf_width(pF, mys, input, i);
    } else if (pF[*i] == '.') {
      cpf_acc(pF, mys, input, i);
    } else if (s21_strcspn(&pF[*i], "lhL") == 0) {
      mys->len = pF[*i];
      (*i)++;
    } else if (s21_strcspn(&pF[*i], "%cdeEfgGosuxXpni") == 0) {
      mys->spec = pF[*i];
      was_spec = 1;
      (*i)++;
    }
  }
}
