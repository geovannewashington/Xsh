// shell.c - simple shell 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// Macros
#define LSH_RL_BUFSIZE 1024

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

// --
// Function Declarations for builtin shell commands:
// --
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);
int lsh_execute(char **args);

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
        if (execvp(args[0], args) == -1) {
            perror("lsh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) { 
        // Fork failed
        perror("lsh");
    } else { 
        // Parent process 
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
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
        status = lsh_execute(args);
    } while (status);

    free(line);
    free(args);
}

// --
// List of builtin commands, followed by their respective functions.
// --
char *builtin_str[] = {
    "cd",
    "help",
    "exit",
};

int (*builtin_func[]) (char **) = {
    &lsh_cd,
    &lsh_exit, 
    &lsh_help
};

int lsh_num_builtins()
{
    return sizeof(builtin_str) / sizeof(char *);
}

// --
// Builtin function imeplementations.
// --
int lsh_cd(char **args)
{
    if (args[1] == NULL) { // We don't have where to cd into
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("lsh");
        }
    }
    return 1;
}

int lsh_help(char **args)
{
    int i;    
    puts("Mrtypo's LSH");
    puts("Type program names and arguments, and hit enter.");
    puts("The following are built in");

    for (int i = 0; lsh_num_builtins(); i++) {
        printf("  %s\n", builtin_str[i]);
    }

    puts("Use the man command for information on other programs.");
    return 1;
}

int lsh_exit(char **args)
{
    return 0;
}

int lsh_execute(char **args)
{
    int i;

    if (args[0] == NULL) {
        // An empty command was entered.
        return 1;
    }

    // Check if the command is a built-in
    for (i = 0; i < lsh_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    // Not a built-in, call functionto start process.
    return lsh_launch(args);
}

int main(int argc, char **argv)
{
    // Load config files, if any.

    // Run command loop.
    lsh_loop();

    // Perform any shutdown/cleanup.
    return EXIT_SUCCESS;
}
