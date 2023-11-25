#include <errno.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROMT "$ "

enum { BAD_ALLOC = 1,
    OK };

int append(char*** words, int* cnt_words, char* word);
void print(char** words, int cnt_words);

int main()
{
    char *line, *word = NULL;
    char** words = NULL;
    int cnt_words = 0;
    while ((line = word = readline(PROMT))) {
        while (word && (word = strtok(word, " \t"))) {
            if (append(&words, &cnt_words, word) == BAD_ALLOC) {
                break;
            }
            word += strlen(word) + 1;
        }
        print(words, cnt_words);
        free(words);
        free(line);
        words = NULL;
    }
    return 0;
}

int append(char*** words, int* cnt_words, char* word)
{
    char** new_array = (char**)realloc(*words, (*cnt_words + 1) * sizeof(char*));
    if (errno == ENOMEM) {
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
