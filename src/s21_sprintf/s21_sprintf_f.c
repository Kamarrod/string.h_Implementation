#include "s21_sprintf.h"
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