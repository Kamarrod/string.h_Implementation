#include "s21_string.h"
void ppts_width_align_left_c(char c, char *str, int col_spaces) {
  char cstr[2];
  cstr[0] = c;
  cstr[1] = '\0';
  s21_strcat(str, cstr);
  for (int i = 0; i < col_spaces; i++) {
    s21_strcat(str, " ");
  }
}

void ppts_width_align_right_c(char c, char *str, int col_spaces,
                              struct info *mys) {
  for (int i = 0; i < col_spaces; i++) {
    if (mys->fl == '0')
      s21_strcat(str, "0");
    else
      s21_strcat(str, " ");
  }
  char cstr[2];
  cstr[0] = c;
  cstr[1] = '\0';
  s21_strcat(str, cstr);
}

void ppts_width_c(struct info *mys, char c, char *str, int j) {
  int col_spaces = mys->width - 1;

  if (col_spaces >= 1) {
    if (mys->fl != '-' && !mys->was_shift) {  //выравнивание правому краю в
                                              //пределах заданной ширины
      ppts_width_align_right_c(c, str, col_spaces, mys);
    } else if (mys->fl == '-' ||
               mys->was_shift) {  //Выравнивание по левому краю в пределах
                                  //заданной ширины
      ppts_width_align_left_c(c, str, col_spaces);
    }
  } else {
    str[j] = c;
    str[j + 1] = '\0';
  }
}