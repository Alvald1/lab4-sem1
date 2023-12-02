// #include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
// #include <string.h>

#define PROMPT "$ "
#define DEL 3
#define DUP 4

enum {
    OK = 1,
    NOT_FOUNDED,
    BAD_ALLOC
};

char* task(char* lines);
int append(char** dest, const char* src);
size_t strlen(const char* str);
void* memcpy(void* dest, const void* src, size_t n);
char* strtok(char* str, const char* delim);
char* readline(const char* prompt);

int main()
{
    char *line = NULL, *result = NULL;
    while ((line = readline(PROMPT))) {
        result = task(line);
        if (result) {
            printf("\n\"%s\"\n", result);
        }
        free(line);
        free(result);
    }
    return 0;
}

int append(char** dest, const char* src)
{
    size_t dest_len = *dest ? strlen(*dest) + 1 : 0;
    size_t src_len = src ? strlen(src) : 0;
    char* new_dest = (char*)realloc(*dest, (dest_len + src_len + 1) * sizeof(char));
    if (new_dest == NULL) {
        return BAD_ALLOC;
    }
    *dest = new_dest;
    memcpy(*dest + dest_len, src, src_len + 1);
    if (dest_len) {
        *(*dest + dest_len - 1) = ' ';
    }
    return OK;
}

char* task(char* line)
{
    int index = 1;
    char *result = NULL, *word = NULL;
    word = strtok(line, " \t");
    do {
        if (word == NULL) {
            continue;
        }
        if (index % DEL == 0) {
            ++index;
            continue;
        } else if (index % DUP == 0) {
            if (append(&result, word) == BAD_ALLOC) {
                return NULL;
            }
        }
        if (append(&result, word) == BAD_ALLOC) {
            return NULL;
        }
        ++index;
    } while ((word = strtok(NULL, " \t")));
    return result;
}

char* readline(const char* prompt)
{
    printf("%s", prompt);
    int size_inc = 10;
    int max_len = size_inc;
    int len = 0, cnt = 0;
    char* new_buffer = NULL;
    char* buffer = (char*)malloc(size_inc);
    char* cur_pos = buffer;
    while (1) {
        if (scanf("%9[^\n]%n", cur_pos, &cnt) == EOF) {
            free(buffer);
            return NULL;
        }
        len += cnt;
        cur_pos += cnt;
        if (len == max_len) {
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
            cur_pos = new_buffer + len;
            buffer = new_buffer;
            *(cur_pos) = '\0';
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
            return OK;
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
    while (*str && is_delim(delim, *str) == OK) {
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
