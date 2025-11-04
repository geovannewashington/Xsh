// parser.c

#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// --
// macros
// --
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

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

