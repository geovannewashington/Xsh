#include "builtin.h"
#include <stdio.h>
#include <unistd.h>

// --
// Macros
// --
#define ARR_SIZE(xs) (sizeof(xs) / sizeof(xs[0]))

struct builtin_commands builtin_cmds_arr[] = {
    {.cmd_command = "cd", .fn = lsh_cd},
    {.cmd_command = "help", .fn = lsh_help},
    {.cmd_command = "exit", .fn = lsh_exit},
};

int lsh_num_builtins()
{
    return ARR_SIZE(builtin_cmds_arr);
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
    (void) args;

    int i;    
    puts("mrtypo's LSH");
    puts("Type program names and arguments, and hit enter.");
    puts("The following are built in");

    for (i = 0; i < lsh_num_builtins(); i++) {
        printf("  %s\n", builtin_cmds_arr[i].cmd_command);
    }

    puts("Use the man command for information on other programs.");
    return 1;
}

int lsh_exit(char **args)
{
    (void) args;
    return 0;
}

