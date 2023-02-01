#include "s21_sprintf.h"
void ppts_width_align_right_i_d(char *num_s, char *str, int col_spaces,
                                int col_zeros, struct info *mys) {
  if (mys->fl != '0') {
    if (num_s[0] != '-' && num_s[0] != '+') {
      for (int i = 0; i < col_spaces; i++)
        strcat(str, " ");
      for (int i = 0; i < col_zeros; i++)
        strcat(str, "0");
    
    if(mys->block_zero==0)
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
    if(mys->block_zero==0)
      strcat(str, &num_s[1]);
    }
  } else if (mys->fl == '0') { //Заполняет число слева нулями (0) вместо
                               //пробелов, где указан спецификатор ширины
    ppts_width_fill_nulls(num_s, str, col_spaces, col_zeros, mys);
  }
}

void ppts_width_align_left_i_d(char *num_s, char *str, int col_spaces,
                               int col_zeros, struct info *mys) {

  if (num_s[0] != '-' && num_s[0] != '+') {
    for (int i = 0; i < col_zeros; i++)
    if(mys->block_zero==0)
      strcat(str, "0");
  if(mys->block_zero==0)
    strcat(str, num_s);
  for (int i = 0; i < col_spaces; i++)
      strcat(str, " ");
  } else if (num_s[0] == '-' || num_s[0] == '+') {
    if (num_s[0] == '-')
      strcat(str, "-");
    else
      strcat(str, "+");

    for (int i = 0; i < col_zeros; i++)
    if(mys->block_zero==0)
      strcat(str, "0");
    if(mys->block_zero==0)
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
    //col_zeros = mys->acc - len_num_s;
    //col_spaces = mys->width - mys->acc;

    if(num_s[0] == '+' || num_s[0] == '-')
      col_zeros = mys->acc - len_num_s +1;
    else
      col_zeros = mys->acc - len_num_s;
  }
  if(col_zeros<0)
    col_zeros=0;
  if(mys->block_zero)
    len_num_s = 0;
  col_spaces = mys->width - (len_num_s+col_zeros);
  
  //printf("ppts_width_i_d:CZ%d CS%d\n", col_zeros, col_spaces);
  
  if (col_spaces >= 1 || col_zeros >= 1) {
    if (mys->fl != '-') { //выравнивание правому краю в пределах заданной ширины
      ppts_width_align_right_i_d(num_s, str, col_spaces, col_zeros, mys);
    } else if (mys->fl == '-') { //Выравнивание по левому краю в пределах
                                 //заданной ширины
      ppts_width_align_left_i_d(num_s, str, col_spaces, col_zeros, mys);
    }
  } else {
    strcat(str, num_s);
  }
}

void ppts_acc_i_d(struct info *mys, int len_num_s, char *num_s, char *str) {
  int col_zeros;
  if(num_s[0] == '+' || num_s[0] == '-')
    col_zeros = mys->acc - len_num_s +1;
  else
    col_zeros = mys->acc - len_num_s;
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
    if(mys->block_zero==0)
      strcat(str, num_s);
  }
}