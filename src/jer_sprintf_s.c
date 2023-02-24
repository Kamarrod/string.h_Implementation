#include "s21_string.h"
void ppts_width_align_right_s(struct info *mys, char *s, char *str,
                              int col_spaces) {
  for (int i = 0; i < col_spaces; i++) {
    if (mys->fl == '0')
      s21_strcat(str, "0");
    else
      s21_strcat(str, " ");
  }
  if (mys->acc >= 0)
    s21_strncat(str, s, mys->acc);
  else
    s21_strcat(str, s);
}

void ppts_width_align_left_s(struct info *mys, char *s, char *str,
                             int col_spaces) {
  if (mys->acc >= 0)
    s21_strncat(str, s, mys->acc);
  else
    s21_strcat(str, s);
  for (int i = 0; i < col_spaces; i++) {
    if (mys->fl == '0')
      s21_strcat(str, "0");
    else
      s21_strcat(str, " ");
  }
}
void ppts_acc_s(struct info *mys, char *s, char *str) {
  s21_strncat(str, s, mys->acc);
}

void ppts_width_s(struct info *mys, char *s, char *str) {
  int col_spaces;
  unsigned macc = mys->acc;
  if (s21_strlen(s) <=
      macc) {  //точность больше или = длины слова => пишем все слово
    col_spaces = mys->width - s21_strlen(s);
  } else {  //точность меньше длины слова
    col_spaces = mys->width - mys->acc;
  }

  if (col_spaces >= 1) {
    if (mys->fl !=
        '-') {  //выравнивание правому краю в пределах заданной ширины
      ppts_width_align_right_s(mys, s, str, col_spaces);
    } else {  //Выравнивание по левому краю в пределах
              //заданной ширины
      ppts_width_align_left_s(mys, s, str, col_spaces);
    }
  } else if (mys->acc >= 0) {
    ppts_acc_s(mys, s, str);
  } else {
    s21_strcat(str, s);
  }
}
