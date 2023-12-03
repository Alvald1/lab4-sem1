#include "lib.h"
#include <stdio.h>

int is_delim(const char* delim, char c);

char* readline(const char* prompt)
{
    printf("%s", prompt);
    int size_inc = 10;
    int len = 0, cnt, max_len = size_inc + 1;
    char* new_buffer = NULL;
    char* buffer = (char*)malloc(max_len);
    char* cur_pos = buffer;
    while (1) {
        cnt = 0;
        if (scanf("%10[^\n]%n", cur_pos, &cnt) == EOF) {
            free(buffer);
            return NULL;
        }
        len += cnt;
        cur_pos += cnt;
        if (cnt == size_inc) {
            new_buffer = (char*)realloc(buffer, max_len += size_inc);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }
            cur_pos = new_buffer + len;
            buffer = new_buffer;
        } else {
            new_buffer = (char*)realloc(buffer, len + 1);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
            cur_pos = new_buffer + len;
            *cur_pos = '\0';
            break;
        }
    }
    scanf("%*c");
    return buffer;
}

int is_delim(const char* delim, char c)
{
    while (*delim) {
        if (*delim++ == c) {
            return __OK;
        }
    }
    return NOT_FOUNDED;
}

char* strtok(char* str, const char* delim)
{
    char* end;
    static char* save_ptr = NULL;
    if (save_ptr == NULL && str == NULL) {
        return NULL;
    }
    if (str == NULL) {
        str = save_ptr;
    }
    while (*str && is_delim(delim, *str) == __OK) {
        ++str;
    }
    if (*str == '\0') {
        save_ptr = str;
        return NULL;
    }
    end = str;
    while (*end && is_delim(delim, *end) == NOT_FOUNDED) {
        ++end;
    }
    if (*end == '\0') {
        save_ptr = end;
        return str;
    }
    *end = '\0';
    save_ptr = end + 1;
    return str;
}

void* memcpy(void* dest, const void* src, size_t n)
{
    char* new_dest = dest;
    char* csrc = (char*)src;
    if (n > strlen(src) + 1 || new_dest == NULL) {
        return NULL;
    }
    while (n--) {
        *new_dest++ = *csrc++;
    }
    return dest;
}

size_t strlen(const char* s)
{
    size_t n;
    for (n = 0; *s != '\0'; ++s) {
        ++n;
    }
    return n;
}
