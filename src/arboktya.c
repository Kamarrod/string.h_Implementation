#include "arboktya.h"
#include <stdlib.h>


char unknownError[25] = "Unknown error           ";
const int indexOfStartNumber = 14;
const int unknownErrorLength = 25;

#ifdef __APPLE__
  static char* macosErrors[107] = {"Undefined error : 0", "Operation not permitted","No such file or directory",
  "No such process","Interrupted system call","Input/output error","Device not configured",
  "Argument list too long","Exec format error","Bad file descriptor","No child processes",
  "Resource deadlock avoided","Cannot allocate memory","Permission denied","Bad address",
  "Block device required","Resource busy","File exists","Cross-device link","Operation not supported by device",
  "Not a directory","Is a directory","Invalid argument","Too many open files in system","Too many open files",
  "Inappropriate ioctl for device","Text file busy","File too large","No space left on device","Illegal seek",
  "Read-only file system","Too many links","Broken pipe","Numerical argument out of domain","Result too large",
  "Resource temporarily unavailable","Operation now in progress","Operation already in progress",
  "Socket operation on non-socket","Destination address required","Message too long","Protocol wrong type for socket",
  "Protocol not available","Protocol not supported","Socket type not supported","Operation not supported",
  "Protocol family not supported","Address family not supported by protocol family","Address already in use",
  "Can't assign requested address","Network is down","Network is unreachable","Network dropped connection on reset",
  "Software caused connection abort","Connection reset by peer","No buffer space available","Socket is already connected",
  "Socket is not connected","Can't send after socket shutdown","Too many references: can't splice","Operation timed out",
  "Connection refused","Too many levels of symbolic links","File name too long","Host is down","No route to host",
  "Directory not empty","Too many processes","Too many users","Disc quota exceeded","Stale NFS file handle",
  "Too many levels of remote in path","RPC struct is bad","RPC version wrong","RPC prog. not avail","Program version wrong",
  "Bad procedure for program","No locks available","Function not implemented","Inappropriate file type or format",
  "Authentication error","Need authenticator","Device power is off","Device error","Value too large to be stored in data type",
  "Bad executable (or shared library)","Bad CPU type in executable","Shared library version mismatch","Malformed Mach-o file",
  "Operation canceled","Identifier removed","No message of desired type","Illegal byte sequence","Attribute not found",
  "Bad message","EMULTIHOP (Reserved)","No message available on STREAM","ENOLINK (Reserved)","No STREAM resources","Not a STREAM",
  "Protocol error","STREAM ioctl timeout","Operation not supported on socket","Policy not found","State not recoverable",
  "Previous owner died","Interface output queue is full"};

#else
  static char* linuxErrors[135] = {"Success", "Operation not permitted", "No such file or directory",
  "No such process", "Interrupted system call", "Input/output error", "No such device or address",
  "Argument list too long", "Exec format error", "Bad file descriptor", "No child processes", "Resource temporarily unavailable",
  "Cannot allocate memory", "Permission denied", "Bad address", "Block device required", "Device or resource busy", "File exists",
  "Invalid cross-device link", "No such device", "Not a directory", "Is a directory", "Invalid argument", "Too many open files in system",
  "Too many open files", "Inappropriate ioctl for device", "Text file busy", "File too large", "No space left on device", "Illegal seek",
  "Read-only file system", "Too many links", "Broken pipe", "Numerical argument out of domain", "Numerical result out of range", "Resource deadlock avoided",
  "File name too long", "No locks available", "Function not implemented", "Directory not empty", "Too many levels of symbolic links", "Unknown error 41",
  "No message of desired type", "Identifier removed", "Channel number out of range", "Level 2 not synchronized", "Level 3 halted", "Level 3 reset",
  "Link number out of range", "Protocol driver not attached", "No CSI structure available", "Level 2 halted", "Invalid exchange", "Invalid request descriptor",
  "Exchange full", "No anode", "Invalid request code", "Invalid slot", "Unknown error 58", "Bad font file format", "Device not a stream", "No data available",
  "Timer expired", "Out of streams resources", "Machine is not on the network", "Package not installed", "Object is remote", "Link has been severed",
  "Advertise error", "Srmount error", "Communication error on send", "Protocol error", "Multihop attempted", "RFS specific error", "Bad message",
  "Value too large for defined data type", "Name not unique on network", "File descriptor in bad state", "Remote address changed",
  "Can not access a needed shared library", "Accessing a corrupted shared library", ".lib section in a.out corrupted",
  "Attempting to link in too many shared libraries", "Cannot exec a shared library directly", "Invalid or incomplete multibyte or wide character",
  "Interrupted system call should be restarted", "Streams pipe error", "Too many users", "Socket operation on non-socket", "Destination address required",
  "Message too long", "Protocol wrong type for socket", "Protocol not available", "Protocol not supported", "Socket type not supported", "Operation not supported",
  "Protocol family not supported", "Address family not supported by protocol", "Address already in use", "Cannot assign requested address", "Network is down",
  "Network is unreachable", "Network dropped connection on reset", "Software caused connection abort", "Connection reset by peer", "No buffer space available",
  "Transport endpoint is already connected", "Transport endpoint is not connected", "Cannot send after transport endpoint shutdown", "Too many references: cannot splice",
  "Connection timed out", "Connection refused", "Host is down", "No route to host", "Operation already in progress", "Operation now in progress", "Stale file handle",
  "Structure needs cleaning", "Not a XENIX named type file", "No XENIX semaphores available", "Is a named type file", "Remote I/O error", "Disk quota exceeded",
  "No medium found", "Wrong medium type", "Operation canceled", "Required key not available", "Key has expired", "Key has been revoked", "Key was rejected by service",
  "Owner died", "State not recoverable", "Operation not possible due to RF-kill", "Memory page has hardware error"};
#endif

// int main() {

//   return 0;
// }

// Добавляет строку, на которую указывает src, в конец строки, на которую указывает dest, длиной до n символов.
char* s21_strncat(char *dest, const char *src, size_t n) {
  char* ptr = dest + s21_strlen(dest);
  size_t srcLength = s21_strlen(src);
  for(size_t i = 0; i < srcLength && i < n; ++i) {
    *ptr = *src;
    ++ptr;
    ++src;
  }
  *ptr = '\0';

  return dest;
}

// // Выполняет поиск во внутреннем массиве номера ошибки errnum и возвращает указатель на строку с сообщением об ошибке.
// // Нужно объявить макросы, содержащие массивы сообщений об ошибке для операционных систем mac и linux.
// // Описания ошибок есть в оригинальной библиотеке. Проверка текущей ОС осуществляется с помощью директив.
char* s21_strerror(int errnum) {
  #ifdef __APPLE__
    return errnum < 0 || errnum> 105 ? "Unknown error" : errnum == 0 ? "Undefined error"
      : macosErrors[errnum];
  #else
    if(errnum < 0 || errnum > 133) {
      refreshUnknownError(errnum);
      return unknownError;
    }
    return linuxErrors[errnum];
  #endif
}

void refreshUnknownError(int errnum) {
  for(int i = indexOfStartNumber; i < unknownErrorLength; ++i)
    unknownError[i] = ' ';
  char* errnumString = getNumberFromInt(errnum);
  for(size_t i = 0; i < s21_strlen(errnumString); ++i)
    unknownError[indexOfStartNumber + i] = errnumString[i];
  unknownError[indexOfStartNumber + s21_strlen(errnumString)] = '\0';
  free(errnumString);
}

char* getNumberFromInt(int number) {
  int digitCount = number < 0 ? 2 : 1;
  int copy = number < 0 ? -number : number;
  while(copy / 10 > 0) {
    ++digitCount;
    copy /= 10;
  }
  char* result = malloc(sizeof(char) * (digitCount + 1));
  if(result != NULL) {
    int endIndex = 0;
    if(number < 0) {
      result[0] = '-';
      number = -number;
      endIndex = 1;
    }
    for(int i = digitCount - 1; i >= endIndex; --i) {
      result[i] = number % 10 + '0';
      number /= 10;
    }
    result[digitCount] = '\0';
  }

  return result;
}

// Разбивает строку str на ряд токенов, разделенных delim.
char* s21_strtok(char* str, const char *delim) {
  static char* ptr = NULL;
  if(str != NULL)
    ptr = str;
  else if(ptr == NULL)
    return ptr;
  str = ptr + strspn(ptr, delim);
  ptr = str + strcspn(str, delim);
  if(str == ptr) {
    ptr = NULL;
    return str;
  }
  if(*ptr) {
    *ptr = '\0';
    ptr++;
  } else {
    ptr = NULL;
  }

  return str;
}


// Вычисляет длину строки str, не включая завершающий нулевой символ.
 size_t s21_strlen(const char *str) {
  size_t size = 0;
  while(str[size])
    ++size;

  return size;
 }

 // Сравнивает строку, на которую указывает str1, со строкой, на которую указывает str2.
int s21_strcmp(const char *str1, const char *str2) {
  while(*str1 != '\0' && *str2 != '\0' && *str1 == *str2) {
    ++str1;
    ++str2;
  }

  return *str1 - *str2 > 0 ? 1 : *str1 - *str2 == 0 ? 0 : -1;
}

int contains(char c, const char* str) {
  int result = 0;
  for(size_t i = 0; i < s21_strlen(str) && result == 0; ++i)
    if(str[i] == c)
      result = 1;
  return result;
}

// Вычисляет длину начального сегмента str1, который полностью состоит из символов str2.
size_t s21_strspn(const char *str1, const char *str2) {
  size_t result = 0;
  size_t lengthStr1 = s21_strlen(str1);
  int find = 1;
  for(size_t i = 0; i < lengthStr1 && find == 1; ++i) {
    if(contains(str1[i], str2) == 1)
      ++result;
    else
      find = 0;
  }

  return result;
}

// Вычисляет длину начального сегмента str1, который полностью состоит из символов, не входящих в str2.
size_t s21_strcspn(const char *str1, const char *str2) {
  size_t result = 0;
  size_t lengthStr1 = s21_strlen(str1);
  int find = 1;
  for(size_t i = 0; i < lengthStr1 && find == 1; ++i) {
    if(contains(str1[i], str2) == 0)
      ++result;
    else
      find = 0;
  }

  return result;
}

// Добавляет строку, на которую указывает src, в конец строки, на которую указывает dest.
char* s21_strcat(char *dest, const char *src) {
  char* ptr = dest + s21_strlen(dest);
  size_t srcLength = s21_strlen(src);
  for(size_t i = 0; i < srcLength; ++i) {
    *ptr = *src;
    ++ptr;
    ++src;
  }
  *ptr = '\0';

  return dest;
}

// Сравнивает первые n байтов str1 и str2.
int s21_memcmp(const void* str1, const void* str2, size_t n) {
  int result = 0;
  const unsigned char* _str1 = str1;
  const unsigned char* _str2 = str2;
  for(size_t i = 0; i < n && result == 0; ++i) {
    if(*_str1 != *_str2)
      result = *_str1 - *_str2;
    ++_str1;
    ++_str2;
  }

  return result > 0 ? 1 : result == 0 ? 0 : -1;
}

// Сравнивает не более первых n байтов str1 и str2.
int s21_strncmp(const char *str1, const char *str2, size_t n) {
  int result = 0;
  for(size_t i = 0; i < n && result == 0; ++i) {
    if(*str1 != *str2)
      result = *str1 - *str2;
    ++str1;
    ++str2;
  }

  return result > 0 ? 1 : result == 0 ? 0 : -1;
}

void* s21_to_lower(const char* str) {
    char* result = NULL;
    if(str != NULL) {
        result = malloc((s21_strlen(str) + 1) * sizeof(char));
        if(result != NULL) {
            for(size_t i = 0; i < s21_strlen(str); ++i) {
                result[i] = str[i];
                if(str[i] >= 'A' && str[i] <= 'Z')
                    result[i] += 'a' - 'A';
            }
            result[s21_strlen(str)] = '\0';
        }
    }

    return result;
}

void* s21_trim(const char* src, const char* trim_chars) {
    char* result = NULL;
    if(src != NULL) {
      if(s21_strlen(src) == 0) result = "";
      else if(trim_chars == NULL || s21_strlen(trim_chars) == 0) result = s21_trim(src, " ");
      else {
        int left = 0, right = s21_strlen(src) - 1;
        while(left < (int)s21_strlen(src) && contains(src[left], trim_chars)) {
          ++left;
        }
        while(right >= 0 && contains(src[right], trim_chars)) {
          --right;
        }
        if(left <= right) {
          result = malloc(sizeof(char) * (right - left + 2));
          if(result != NULL) {
            for(int i = 0; i < (right - left + 1); ++i)
              result[i] = src[left + i];
            result[right - left + 1] = '\0';
          }
        } else result = "";
      }
    }

    return result;
}