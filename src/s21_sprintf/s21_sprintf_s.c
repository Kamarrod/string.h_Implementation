#include "s21_sprintf.h"
void ppts_width_align_right_s(struct info *mys, char *s, char *str,
                              int col_spaces) {
  for (int i = 0; i < col_spaces; i++) {
    if (mys->fl == '0')
      strcat(str, "0");
    else
      strcat(str, " ");
  }
  if (mys->acc >= 0)
    strncat(str, s, mys->acc);
  else
    strcat(str, s);
}

void ppts_width_align_left_s(struct info *mys, char *s, char *str,
                             int col_spaces) {
  if (mys->acc >= 0)
    strncat(str, s, mys->acc);
  else
    strcat(str, s);
  for (int i = 0; i < col_spaces; i++) {
    if (mys->fl == '0')
      strcat(str, "0");
    else
      strcat(str, " ");
  }
}
void ppts_acc_s(struct info *mys, char *s, char *str) {
  strncat(str, s, mys->acc);
}

void ppts_width_s(struct info *mys, char *s, char *str) {
  int col_spaces;
  if (strlen(s) <=
      mys->acc) {  //точность больше или = длины слова => пишем все слово
    col_spaces = mys->width - strlen(s);
  } else {  //точность меньше длины слова
    col_spaces = mys->width - mys->acc;
  }

  if (col_spaces >= 1) {
    if (mys->fl !=
        '-') {  //выравнивание правому краю в пределах заданной ширины
      ppts_width_align_right_s(mys, s, str, col_spaces);
    } else if (mys->fl == '-') {  //Выравнивание по левому краю в пределах
                                  //заданной ширины
      ppts_width_align_left_s(mys, s, str, col_spaces);
    }
  } else if (mys->acc >= 0) {
    ppts_acc_s(mys, s, str);
  } else {
    strcat(str, s);
  }
}
