#include "jer_sprintf.h"

void ppts_acc_u(struct info *mys, int len_num_s, char *num_s, char *str) {
  int col_zeros = mys->acc - len_num_s;
  if (col_zeros >= 1) {
    for (int i = 0; i < col_zeros; i++) s21_strcat(str, "0");
    s21_strcat(str, num_s);
  } else {
    if (mys->block_zero == 0) s21_strcat(str, num_s);
  }
}
