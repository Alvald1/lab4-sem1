#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROMPT "$ "

char* task(char* lines);

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
    if (lines) {
        result = task(lines);
        printf("%s", result);
    }
    free(lines);
    return 0;
}

char* task(char* lines)
{
    char *result = NULL, *line = NULL;
    line = strtok(lines, "\n");
    do {
        printf("%s\n", line);
    } while ((line = strtok(NULL, "\n")));
    return result;
}
