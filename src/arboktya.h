#ifndef ARBOKTYA_H
#define ARBOKTYA_H

#include <stdio.h>
//#include <string.h>
#include <stdlib.h>

s21_size_t s21_strlen(const char *str);  // ++
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);  // ++
int s21_strcmp(const char *str1, const char *str2);  // ++
int s21_strncmp(const char *str1, const char *str2, s21_size_t n); // ++
char* s21_strtok(char *str, const char *delim);
char* s21_strerror(int errnum);  // ++
char* s21_strcat(char *dest, const char *src); // ++
char* s21_strncat(char *dest, const char *src, s21_size_t n); // ++
s21_size_t s21_strspn(const char *str1, const char *str2); // ++
s21_size_t s21_strcspn(const char *str1, const char *str2); // ++

void* s21_to_lower(const char *str);  // ++
void* s21_trim(const char *src, const char *trim_chars); // ++

int contains(char c, const char* str);
void refreshUnknownError(int errnum);
char* getNumberFromInt(int number);


#endif // ARBOKTYA_H