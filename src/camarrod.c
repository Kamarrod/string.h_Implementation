#include "camarrod.h"

char *s21_strchr(const char *str, int c) { // check
    int find = -1;
    s21_size_t shift = 0;
    if (str != s21_NULL) {
        do {
            if (str[shift] == c) find = 1;
        } while (find == -1 && str[shift++] != '\0');
    }
    return find == -1 ? s21_NULL : (char*)str + shift;
}

 char *s21_strcpy(char *dest, const char *src) { // check
    char *start = dest;
    if (dest != s21_NULL) {
        while(*src != '\0') {
            *dest = *src;
            dest++;
            src++;
        }
        *dest = '\0';
    }
    return start;
 }

char *s21_strncpy(char *dest, const char *src, s21_size_t n) { // check
    char * prom = s21_NULL;
    if (src != s21_NULL) {
        prom = dest;
        s21_size_t i = 0;
        for ( ; i < n && src[i] != '\0'; i++) {
            dest[i] = src[i];
        }
        for (; i < n; i++) {
            dest[i] = '\0';
        }
    }
    return prom;
}

char *s21_strpbrk(const char *str1, const char *str2) { // check
    int find = -1;
    s21_size_t shift  = 0;
    if (str1!= s21_NULL && str2!= s21_NULL) {
        do {
           for (s21_size_t j = 0; j < strlen(str2) && find == -1; j++) {
            if (str1[shift] == str2[j]) find = 1;
           }
        } while (find == -1 && str1[shift++] != '\0');
    }
    return find == -1 ? s21_NULL : (char*)str1 + shift;
}

char *s21_strrchr(const char *str, int c) { //check
    int find = -1;
    s21_size_t shift = 0;
    if (str != s21_NULL) {
        s21_size_t i = 0;
        do {
            if (str[i] == c) {
                find = 1;
                shift = i;
            }
        } while (str[i++] != '\0');
    }
    return find == -1 ? s21_NULL : (char*)str + shift;
}

char *s21_strstr(const char *haystack, const char *needle) { // check
  int first = 0;
  int flag;
  s21_size_t shift = 0;
  if (haystack != s21_NULL && needle != s21_NULL) {
    s21_size_t lenOne = strlen(haystack);
    s21_size_t lenTwo = strlen(needle);
    if (lenOne == lenTwo && lenOne == 0 && *haystack == '\0' && *needle == '\0') {
        first = 1;
        shift = 1;
    }
    for (s21_size_t i = 0; i < lenOne && first == 0; i++) {
        flag = 0;
        for (s21_size_t j = 0; j < lenTwo && flag == 0; j++) {
        if (needle[j] != haystack[i + j]) {
            flag = 1;
        }
        }
        shift++;
        if (flag == 0) {
            first = 1;
        }
    }
  }
  return first == 0 ? s21_NULL : (char*)haystack + shift - 1;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {  // check
    int find = -1;
    s21_size_t shift = 0;
    if (str != s21_NULL) {
        while (shift < n && find == -1 && *((char*)str) != '\0') 
        {
            if (*((char*)str + shift) == (char)c) find = 1;
            else 
            {
                *((char*)str) = *((char*)str) + 1; 
                shift++;
            }
        }
    }
    return find == -1 ? s21_NULL : (void*)str + shift;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) { // check
    void* prom = dest;
    while (n--) {
        *((char*)dest++) = *((char*)src++);
    }
    return prom;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
    if (src != NULL && dest != NULL) {
        if (dest < src) { //&& src - dest < (int)n) {
            void *promDest = dest ;
            const void *promSrc = src;
            while (n--) {
                *((char*)promDest++) = *((char*)promSrc++);
            }
            //return dest;
        } 
        if (src < dest ) { //&& dest - src < (int)n) {
            printf("YES\n");
            void *promDest = dest + n;
            const void *promSrc = src + n;
            n = n + 1;
            while (n--) {
                *((char*)promDest--) = *((char*)promSrc--);
            }
            //return dest;
        }
        //s21_memcpy(dest, src, n);
    }
    return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
    void * prom = str;
    if (str != s21_NULL) {
        for (s21_size_t i = 0; i < n; i++) {
            *(char*)(str + i) = c;
        }
    }
    return prom;
}

void *s21_to_upper(const char *str) { // check
    char *copy = s21_NULL;
    if (str != s21_NULL) {
        s21_size_t len = strlen(str);
        const char * prom = str;
        copy = malloc((len + 1) * sizeof(char));
        if (copy) {
            for (s21_size_t i = 0; i < len; i++) {
                if (prom[i] <= 'z' && prom[i] >= 'a')
                    copy[i] = prom[i] - 32;
                else copy[i] = prom[i];
            }
            copy[len] = '\0';
        }
    }
    return (void*)copy;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) { //check 
    char * answer = s21_NULL;
    if (str && src && start_index <= strlen(src)) {
        s21_size_t lenSrc = strlen(src);
        s21_size_t lenStr = strlen(str);
        //else lenStr = 0;
        answer = malloc((lenSrc + lenStr + 1) * sizeof(char));
        for (s21_size_t i = 0; i < lenSrc + lenStr; i++) {
            if (str && start_index <= i && i < start_index + lenStr) answer[i] = str[i - start_index];
            else {
                    if (i >= start_index + lenStr ) answer[i] = src[i - lenStr];
                    else answer[i] = src[i];
            }
        }
        answer[lenSrc + lenStr] = '\0';
    }
    return (void*)answer;
}