#include "s21_sprintf.h"
void ppts_f(struct info *mys, char *num_s, char *str) {

  if(mys->width!=-1){
    
    if(mys->fl=='-' || mys->was_shift)
      strcat(str, num_s);
    // printf("PPTS F:STRLEN NUMS: %ld\n", strlen(num_s));
    // printf("PPTS F:SUBSTRACT: %ld\n", mys->width - strlen(num_s));
    // printf("PPTS res: %ld\n", (mys->width > strlen(num_s)));
    if((mys->width > strlen(num_s))){  
      for (int i = 0; i < mys->width - strlen(num_s);i++) {
        if(mys->fl=='0')
          strcat(str, "0");
        else
          strcat(str, " ");
      }
    }

    if(mys->fl!='-')
      strcat(str, num_s);
  } else {
    strcat(str, num_s);
  }

}