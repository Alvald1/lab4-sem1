#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROMPT "$ "
#define DEL 3
#define DUP 4
enum {
    OK = 1,
    BAD_ALLOC = 2
};

char* task(char* lines);
int append(char** dest, const char* src);

int main()
{
    char *line = NULL, *lines = NULL, *result = NULL;
    size_t lines_len = 0, line_len = 0;
    while ((line = readline(PROMPT))) {
        lines_len = lines ? strlen(lines) + 1 : 0;
        line_len = strlen(line);
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
        printf("%s", result);
    }
    free(result);
    free(lines);
    return 0;
}

int append(char** dest, const char* src)
{
    size_t dest_len = *dest ? strlen(*dest) + 1 : 0;
    char* new_dest = (char*)realloc(*dest, (dest_len + strlen(src) + 1) * sizeof(char));
    if (new_dest == NULL) {
        return BAD_ALLOC;
    }
    *dest = new_dest;
    memcpy(*dest + dest_len, src, strlen(src) + 1);
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
        index = 1;
        result_len = result ? strlen(result) : 0;
        word = strtok_r(line, " \t", &save_word);
        do {
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
        if (result_len) {
            *(result + result_len) = '\n';
        }
    } while ((line = strtok_r(NULL, "\n", &save_line)));
    return result;
}
