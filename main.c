#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// #include "lib/lib.h"

#define PROMPT "$ "
#define DEL 3
#define DUP 4

enum {
    BAD_ALLOC = -5,
    OK = 1
};

char* task(char* lines);
int append(char** dest, const char* src);

int main()
{
    char *line = NULL, *result = NULL;
    while ((line = readline(PROMPT))) {
        clock_t start = clock();
        result = task(line);
        if (result) {
            printf("\n\"%s\"\n", result);
        }
        clock_t end = clock();
        float seconds = (float)(end - start) / CLOCKS_PER_SEC;
        printf("time: %f\n", seconds);
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
