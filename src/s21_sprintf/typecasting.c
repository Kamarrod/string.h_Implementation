#include <math.h>

#include "s21_sprintf.h"

void reverse(char* str, int len) {
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
  int long_min = 0;
  if (x < 0) {
    //костыль для min_long
    if (x == LONG_MIN) {
      x = LONG_MAX;
      long_min = 1;
    } else {
      x = -x;
    }
    neg = 1;
  }

  static char str[1024] = {0};

  //тк статик чтобы убирать мусор между итерациями
  for (int k = 0; k <= 1024; k++) str[k] = '\0';
  int i = 0;

  if (x == 0)
    str[i] = '0';
  else {
    while (x) {
      str[i++] = (x % 10) + '0';
      x = x / 10;
    }
    while (i < d) str[i++] = '0';

    reverse(str, i);
  }
  str[i + 1] = '\0';

  if (neg) {
    for (int j = i + 1; j >= 0; j--) str[j] = str[j - 1];
    str[0] = '-';

    if (long_min) {  ////костыль для min_long продолжение
      str[i] += 1;
    }
    str[i + 2] = '\0';
  }
  return str;
}

char* utoa(unsigned long value) {
  static char str[128] = {0};
  const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
  int i, j;
  unsigned remainder;
  char c;
  int base = 10;
  i = 0;
  do {
    remainder = value % base;
    str[i++] = digits[remainder];
    value = value / base;
  } while (value != 0);
  str[i] = '\0';

  for (j = 0, i--; j < i; j++, i--) {
    c = str[j];
    str[j] = str[i];
    str[i] = c;
  }

  return str;
}
char* ulltoa(unsigned long long x, int d) {
  int neg = 0;
  int long_min = 0;
  if (x < 0) {
    //костыль для min_long
    if (x == LONG_MIN) {
      x = LONG_MAX;
      long_min = 1;
    } else {
      x = -x;
    }
    neg = 1;
  }

  static char str[1024] = {0};

  //тк статик чтобы убирать мусор между итерациями
  for (int k = 0; k <= 1024; k++) str[k] = '\0';
  int i = 0;

  if (x == 0)
    str[i] = '0';
  else {
    while (x) {
      str[i++] = (x % 10) + '0';
      x = x / 10;
    }
    while (i < d) str[i++] = '0';

    reverse(str, i);
  }
  str[i + 1] = '\0';

  if (neg) {
    for (int j = i + 1; j >= 0; j--) str[j] = str[j - 1];
    str[0] = '-';

    if (long_min) {  ////костыль для min_long продолжение
      str[i] += 1;
    }
    str[i + 2] = '\0';
  }
  return str;
}

char* ftoa(long double n, int afterpoint, char c) {
  char* res_d = NULL;
  char res[256];
  res[0]='\0';
    for (int k = 0; k <= 256; k++) res[k] = '\0';
    if (n < 0) {
      n = -n;
      strcat(res, "-");
    } else {
      if (c == '+')
        strcat(res, "+");
      else if (c == ' ')
        strcat(res, " ");
    }

    if (afterpoint != 0) {
      unsigned long long ipart = (unsigned long long)n;
      long double fpart = n - (long double)ipart;

      if ((int)(fpart * 100) >= 95 && afterpoint <= 4) {
        strcat(res, ulltoa(ipart + 1, 0));
        fpart = 0;
      } else {
        strcat(res, ulltoa(ipart, 0));
        fpart = roundl(fpart * pow(10, afterpoint));
      }
      strcat(res, ".");
      if (fpart != 0.0)
        strcat(res, ulltoa((unsigned long long)fpart, afterpoint));
      else {
        for (int i = 0; i < afterpoint; i++) strcat(res, "0");
      }
    } else {
      long double rounded = roundl(n);
      strcat(res, ulltoa((unsigned long long)rounded, 0));
    }


  res_d = malloc((strlen(res)+1) * sizeof(char));
  if(res_d)
    strcpy(res_d, res);
  return res_d;
}