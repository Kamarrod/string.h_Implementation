#include "s21_sprintf.h"
void ppts_width_align_left_c(char c, char *str, int col_spaces, struct info *mys, int j) {
    //strncat(str, &c, 1);
    str[j]=c;
  for (int i = 0; i < col_spaces; i++){
    // if(mys->fl=='0')
    //   strcat(str, "0");
    // else
      strcat(str, " ");
  }
}

void ppts_width_align_right_c(char c, char *str, int col_spaces, struct info *mys, int j) {
  for (int i = 0; i < col_spaces; i++){
    if(mys->fl=='0')
      strcat(str, "0");
    else
      strcat(str, " ");
  }
  //strncat(str, &c, 1);
      str[j]=c;
}

void ppts_width_c(struct info *mys, char c, char *str, int j) {
  int col_spaces = mys->width - 1;

  if (col_spaces >= 1) {
    if (mys->fl != '-' && !mys->was_shift) { //выравнивание правому краю в пределах заданной ширины
      ppts_width_align_right_c(c, str, col_spaces,mys, j);
    } else if (mys->fl == '-' || mys->was_shift) { //Выравнивание по левому краю в пределах
                                 //заданной ширины
      ppts_width_align_left_c(c, str, col_spaces, mys, j);
    }
  } else {
    //strncat(str, &c, 1);
    printf("PPTS: C= %c\n", c);
    str[j]=c;
  }
}