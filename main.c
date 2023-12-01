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
char* strtok_r(char* str, const char* delim, char** saveptr);
char* readline(const char* prompt);

int main()
{
    char *line = NULL, *lines = NULL, *result = NULL;
    size_t lines_len = 0, line_len = 0;
    while ((line = readline(PROMPT))) {
        line_len = strlen(line);
        lines_len = lines ? strlen(lines) + 1 : 0;
        char* new_lines = (char*)realloc(lines, (lines_len + line_len + 2) * sizeof(char));
        if (new_lines == NULL) {
            free(line);
            free(lines);
            return 0;
        }
        lines = new_lines;
        memcpy(lines + lines_len, line, line_len + 1);
        if (lines_len) {
            *(lines + lines_len - 1) = '\n';
        }
        free(line);
    }
    if (lines == NULL) {
        return 0;
    }
    result = task(lines);
    if (result) {
        printf("\n%s", result);
    }
    free(result);
    free(lines);
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

char* task(char* lines)
{
    size_t result_len = 0;
    int index;
    char *result = NULL, *line = NULL, *word = NULL, *save_line = NULL, *save_word = NULL;
    line = strtok_r(lines, "\n", &save_line);
    do {
        if (line == NULL) {
            continue;
        }
        index = 1;
        result_len = result ? strlen(result) : 0;
        word = strtok_r(line, " \t", &save_word);
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
        } while ((word = strtok_r(NULL, " \t", &save_word)));
        if (result_len && result_len < strlen(result)) {
            *(result + result_len) = '\n';
        }
    } while ((line = strtok_r(NULL, "\n", &save_line)));
    return result;
}

char* readline(const char* prompt)
{
    printf("%s", prompt);
    int size_inc = 10;
    char* new_buffer;
    char* buffer = (char*)malloc(size_inc);
    char* cur_pos = buffer;
    int max_len = size_inc;
    int len = 0, cnt = 0, res = 0;
    while (1) {
        res = scanf("%10[^\n]%n", cur_pos, &cnt);
        if (res == EOF) {
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
            cur_pos = new_buffer + (cur_pos - buffer);
            buffer = new_buffer;
        } else {
            new_buffer = (char*)realloc(buffer, len + 1);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }
            cur_pos = new_buffer + (cur_pos - buffer);
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

char* strtok_r(char* str, const char* delim, char** save_ptr)
{
    char* end;
    if (*save_ptr == NULL && str == NULL) {
        return NULL;
    }
    if (str == NULL) {
        str = *save_ptr;
    }
    if (*str == '\0') {
        *save_ptr = str;
        return NULL;
    }
    while (*str && is_delim(delim, *str) == OK) {
        ++str;
    }
    if (*str == '\0') {
        *save_ptr = str;
        return NULL;
    }
    end = str;
    while (*end && is_delim(delim, *end) == NOT_FOUNDED) {
        ++end;
    }
    if (*end == '\0') {
        *save_ptr = end;
        return str;
    }
    *end = '\0';
    *save_ptr = end + 1;
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
