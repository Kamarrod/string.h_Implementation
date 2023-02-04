#include "s21_sprintf.h"
#include <math.h>

char *utoa(unsigned long val, int base) {
  static char buf[128] = {0};
  int i = 30;

  for (; val && i; --i, val /= base)

    buf[i] = "0123456789abcdef"[val % base];
  char *ret_val;
  ret_val = &buf[i +1];
  return ret_val;
}

void reverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

char* itoa(long x, int d) {
  int neg = 0;
  int long_min=0;
  if (x < 0) {
    //костыль для min_long
    if(x==LONG_MIN){
      x=LONG_MAX;
      long_min=1;
    } else {
      x = -x;
    }
    neg = 1;
  }


  static char str[1024] = {0};
  
  //тк статик чтобы убирать мусор между итерациями
  for (int k = 0; k <= 1024; k++)
      str[k] = '\0';
  int i = 0;
  
    if(x==0)
      str[i] = '0';
    else {
      while (x) {
          str[i++] = (x % 10) + '0';
          x = x / 10;
      }
      while (i < d)
        str[i++] = '0';

      reverse(str, i);
    }
    str[i+1] = '\0';
    

    if(neg){
      for (int j=i+1; j>=0; j--)
        str[j] = str[j-1];
      str[0]='-';

      if(long_min){////костыль для min_long продолжение
        str[i] +=1;
      } 
      str[i+2] = '\0';
    }
    return str;
}

// char* ftoa(long double n, int afterpoint, char c) {
//     static char res[128] = {0};
//     for (int k = 0; k <= 1024; k++)
//       res[k] = '\0';
//     char *fparts;
//     char* iparts;
//     int i;
//     if(n<0) {
//       n=-n;
//       res[0] = '-';
//     } else {
//       if(c=='+')
//         res[0] = '+';
//       else if(c==' ')
//         res[0] = ' ';
//     }
//     printf("FTOA:RES0:%s\n", res);
//     long ipart = (long)n;
//     long double fpart = n - (long double)ipart;    
   
//     i = strlen(res);
//     printf("FTOA:I1:%ld\n", i);
    
//     iparts = itoa(ipart,0);
//     //printf("FTOA:IPART:%ld\n", ipart);
//     printf("FTOA:IPARTS:%s\n", iparts);
    
//     for(int k=0; k < strlen(iparts);k++){
//       res[i] = iparts[k];
//       printf("FTOA:CYCLE:res[i]: %c\n", res[i]);
//       printf("FTOA:CYCLE:iparts[k]: %c\n", iparts[k]);
//       i++;
//     }
//     printf("--------------------------------------\n");
//     for(int k=0; k < 2;k++){
//       printf("FTOA:CYCLE:iparts[k]: %c\n", iparts[k]);
//     }

//     //res[i] = '\0';
//     //strcat(res, itoa(ipart,0));
//     //i = strlen(res);
//     printf("FTOA:I1:%ld\n", i);
//     printf("FTOA:RES1:%s\n", res);
   
   
   
//     if (afterpoint != 0) {
//         res[i] = '.';

//         fpart = roundl(fpart * pow(10, afterpoint));
//         //fpart = fpart * pow(10, afterpoint);
//         //strcat(res, itoa((long)fpart, afterpoint));
        
//         //printf("FTOA:FPART:DEC:LD:%ld\n", (long)fpart);
//         //printf("FTOA:FPART:STR:%s\n", itoa((long)fpart, afterpoint));
//     }
//     printf("FTOA:RES2:%s\n", res);
//     return res;
// }


char *__utoa (unsigned long value){
  static char str[128] = {0};
  const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
  int i, j;
  unsigned remainder;
  char c;
  int base = 10;
  /* Convert to string. Digits are in reverse order.  */
  i = 0;
  do 
    {
      remainder = value % base;
      str[i++] = digits[remainder];
      value = value / base;
    } while (value != 0);  
  str[i] = '\0'; 
  
  /* Reverse string.  */
  for (j = 0, i--; j < i; j++, i--)
    {
      c = str[j];
      str[j] = str[i];
      str[i] = c; 
    }       
  
  return str;
}



// char* ftoa(long double n, int afterpoint, char c) {
//     static char res[128] = {0};
//     for (int k = 0; k <= 1024; k++)
//       res[k] = '\0';
//     int i;
//     if(n<0) {
//       n=-n;
//       res[0] = '-';
//     } else {
//       if(c=='+')
//         res[0] = '+';
//       else if(c==' ')
//         res[0] = ' ';
//     }
//     long ipart = (long)n;
//     long double fpart = n - (long double)ipart;     
//     strcat(res, itoa(ipart,0));
//     i = strlen(res);   
//     if (afterpoint != 0) {
//         res[i] = '.';
//         fpart = roundl(fpart * pow(10, afterpoint));
//         strcat(res, itoa((long)fpart, afterpoint));
//     }
//     return res;
// }

// char* ftoa(long double n, int afterpoint, char c) {
//     static char res[128] = {0};
//     for (int k = 0; k <= 1024; k++)
//       res[k] = '\0';
//     int i;


//     if(n<0) {
//       n=-n;
//       res[0] = '-';
//     } else {
//       if(c=='+')
//         res[0] = '+';
//       else if(c==' ')
//         res[0] = ' ';
//     }

//     if(afterpoint!=0){
//       long ipart = (long)n;
//       long double fpart = n - (long double)ipart;     
//       strcat(res, itoa(ipart,0));
//       i = strlen(res);   

//         res[i] = '.';
//         fpart = roundl(fpart * pow(10, afterpoint));
//         strcat(res, itoa((long)fpart, afterpoint));
//     } else {
//         long double rounded = roundl(n);
//         strcat(res, itoa((long)rounded,0));
//     }

//     return res;
// }
char* ulltoa(unsigned long long x, int d) {
  int neg = 0;
  int long_min=0;
  if (x < 0) {
    //костыль для min_long
    if(x==LONG_MIN){
      x=LONG_MAX;
      long_min=1;
    } else {
      x = -x;
    }
    neg = 1;
  }


  static char str[1024] = {0};
  
  //тк статик чтобы убирать мусор между итерациями
  for (int k = 0; k <= 1024; k++)
      str[k] = '\0';
  int i = 0;
  
    if(x==0)
      str[i] = '0';
    else {
      while (x) {
          str[i++] = (x % 10) + '0';
          x = x / 10;
      }
      while (i < d)
        str[i++] = '0';

      reverse(str, i);
    }
    str[i+1] = '\0';
    

    if(neg){
      for (int j=i+1; j>=0; j--)
        str[j] = str[j-1];
      str[0]='-';

      if(long_min){////костыль для min_long продолжение
        str[i] +=1;
      } 
      str[i+2] = '\0';
    }
    return str;
}

char* ftoa(long double n, int afterpoint, char c) {

char *res = NULL;
res = malloc((256) * sizeof(char));
if (res) {
    for (int k = 0; k <= 256; k++)
      res[k] = '\0';
    int i;
    if(n<0) {
      n=-n;
      strcat(res, "-");
    } else {
      if(c=='+')
        strcat(res, "+");
      else if(c==' ')
        strcat(res, " ");
    }

    if(afterpoint!=0){
      unsigned long long ipart =  (unsigned long long)n;
      long double fpart = n - (long double)ipart;     
      strcat(res, ulltoa(ipart,0));
      i = strlen(res);   

        res[i] = '.';
        fpart = roundl(fpart * pow(10, afterpoint));
        if(fpart!=0.0)
          strcat(res, ulltoa((unsigned long long)fpart, afterpoint));
        else {
          for (int i=0; i< afterpoint; i++)
            strcat(res, "0");
        }
    } else {
        long double rounded = roundl(n);
        strcat(res, ulltoa((unsigned long long)rounded,0));
    }
}
    return res;
}