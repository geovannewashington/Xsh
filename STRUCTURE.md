Xsh/
├── LICENSE
├── README.md
├── STRUCTURE.md
├── TODO.md
├── Makefile
├── main.c                  # entry point
├── shell/                  # core shell logic
│   ├── shell.h             # shared declarations
│   ├── parser.c            # command parsing, quotes, backslashes
│   ├── parser.h
│   ├── builtin.c           # builtin commands (cd, help, exit, etc.)
│   ├── builtin.h
│   ├── executor.c          # launching external commands, pipes, redirection
│   ├── executor.h
│   └── config.c            # load config files (e.g., .xshrc)
│       └── config.h
├── tests/                  # optional: unit or integration tests
│   └── test_shell.c
└── docs/                   # optional: documentation or diagrams
    └── ascii_diagrams.md
