// shell.c - simple shell 

#include <stdio.h>
#include <stdlib.h>

// Macros
#define LSH_RL_BUFSIZE 1024

char *lsh_read_line(void)
{
    int bufsize = LSH_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Read a character.
        c = getchar();

        // If we hit EOF, replace it with a null character and return;
        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer; // Nothing more to read
        } else {
            buffer[position] = c;
        }
        position++;

        // If we have exceeded the buffer, reallocate.
        if (position >= bufsize) {
            bufsize += LSH_RL_BUFSIZE; // 2048bytes
            buffer = realloc(buffer, bufsize);
            
            if (!buffer) {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

void lsh_loop(void)
{
    char *line;
    char **args;
    int status; // 0 = false | non-zero = true

    do {
        printf("$ "); // I'm assuming this is the prompt symbol
        line = lsh_read_line();
        args = lsh_split_line(line);
        status = lsh_execute(args);
    } while (status);

    free(line);
    free(args);
}

int main(int argc, char **argv)
{
    // Load config files, if any.

    // Run command loop.
    lsh_loop();

    // Perform any shutdown/cleanup.
    return EXIT_SUCCESS;
}
