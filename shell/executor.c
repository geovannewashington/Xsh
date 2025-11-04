#include "executor.h"
#include "builtin.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int lsh_launch(char **args)
{
    pid_t pid;
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
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    
    return 1;
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
        if (strcmp(args[0], builtin_cmds_arr[i].cmd_command) == 0) {
            return (*builtin_cmds_arr[i].fn)(args);
        }
    }

    // Not a built-in, call functionto start process.
    return lsh_launch(args);
}
