#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROMPT "$ "

enum {
    BAD_ALLOC = 1,
    OK
};

int append(char*** words, int* cnt_words, char* word);
void print(char** words, int cnt_words);

int main()
{
    char *line, *lines = NULL;
    size_t lines_len;
    while ((line = readline(PROMPT))) {
        lines_len = lines ? strlen(lines) + 1 : 0;
        char* new_lines = (char*)realloc(lines, (lines_len + strlen(line) + 1) * sizeof(char));
        if (new_lines == NULL) {
            free(line);
            free(lines);
            return 0;
        }
        lines = new_lines;
        memcpy(lines + lines_len, line, strlen(line) + 1);
        if (lines_len) {
            *(lines + lines_len - 1) = '\n';
        }
        free(line);
    }
    printf("%s", lines);
    free(lines);
    return 0;
}

int append(char*** words, int* cnt_words, char* word)
{
    char** new_array = (char**)realloc(*words, (*cnt_words + 1) * sizeof(char*));
    if (new_array == NULL) {
        return BAD_ALLOC;
    }
    *words = new_array;
    *((*words) + (*cnt_words)) = word;
    ++*cnt_words;
    return OK;
}

void print(char** words, int cnt_words)
{
    while (cnt_words--) {
        printf("%s\n", *words++);
    }
}
