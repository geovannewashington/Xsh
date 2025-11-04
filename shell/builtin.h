// builtin.h

#ifndef BUILTIN_H
#define BUILTIN_H

// --
// Function prototypes
// --
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);
int lsh_num_builtins();

// --
// Structs
// --
struct builtin_commands {
    const char* cmd_command;
    int(*fn)(char **);
}; 

extern struct builtin_commands builtin_cmds_arr[];

#endif
