#include "s21_string.h"
void ppts_f(struct info *mys, char *num_s, char *str) {
  int len_s;
  if (num_s != s21_NULL)
    len_s = s21_strlen(num_s);
  else
    len_s = 0;

  if (mys->width != -1) {
    if (mys->fl == '-' ||
        mys->was_shift) {  //если - то сначала пишем число потом
      s21_strcat(str, num_s);
      if ((mys->width > len_s)) {
        for (int i = 0; i < mys->width - len_s; i++) {
          s21_strcat(str, " ");
        }
      }
    }
    if (mys->fl != '-' && !mys->was_shift) {
      int col_zeros_spaces = mys->width - len_s;
      if (col_zeros_spaces > 0) {
        char *p1 = NULL;
        p1 = malloc((mys->width + 1) * sizeof(char));

        if (p1) {
          p1[0] = '\0';
          if (num_s[0] == ' ' || num_s[0] == '+' || num_s[0] == '-') {
            for (int i = 0; i < col_zeros_spaces; i++)
              if (mys->fl != '0') s21_strcat(p1, " ");
            s21_strncat(p1, num_s, 1);
            for (int i = 0; i < col_zeros_spaces; i++)
              if (mys->fl == '0') s21_strcat(p1, "0");
            s21_strcat(p1, &num_s[1]);
          } else {
            for (int i = 0; i < col_zeros_spaces; i++) {
              if (mys->fl == '0')
                s21_strcat(p1, "0");
              else
                s21_strcat(p1, " ");
            }
            s21_strcat(p1, num_s);
          }
          s21_strcat(str, p1);
          free(p1);
        }

      } else {
        s21_strcat(str, num_s);
      }
    }
  } else {
    s21_strcat(str, num_s);
  }
}
