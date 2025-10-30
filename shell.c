// shell.c - simple shell 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Macros
#define LSH_RL_BUFSIZE 1024

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

char *lsh_read_line(void)
{
    int bufsize = LSH_RL_BUFSIZE; // Initially a KiB
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

char **lsh_split_line(char *line)
{
    int bufsize = LSH_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token; 
    
    // --
    // If malloc fails for some return it returns NULL
    // and NULL in a boolan context in C evaluates as false
    // --
    if (!tokens) {
        fprintf(stderr, "lsh: allocation error:\n");
        exit(EXIT_FAILURE);
    }
    
    token = strtok(line, LSH_TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;
        
        // --
        // Check if we're out of bounds
        // --
        if (position >= bufsize) {
            bufsize += LSH_TOK_BUFSIZE; // 2nd: 128 bytes
            tokens = realloc(tokens, bufsize * sizeof(char *));
            
            if (!tokens) {
                fprintf(stderr, "lsh: allocation error:\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, LSH_TOK_DELIM);
    }
    return tokens;
}

int lsh_launch(char **args)
{
    pid_t pid, wpid;
    int status;
    
    pid = fork();

    if (pid == 0) { 
        // Child process                
    } else if (pid < 0) { 
        // Fork failed
        perror("lsh");
    } else { 
        // Parent process 
    }
    
    return 1;
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
        // status = lsh_execute(args);
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
