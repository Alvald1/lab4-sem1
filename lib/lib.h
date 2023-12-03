#ifndef __MY_LIB__
#define __MY_LIB__
#include <stdlib.h>

enum {
    __OK = 1,
    NOT_FOUNDED
};

size_t strlen(const char* str);
void* memcpy(void* dest, const void* src, size_t n);
char* strtok(char* str, const char* delim);
char* readline(const char* prompt);

#endif
