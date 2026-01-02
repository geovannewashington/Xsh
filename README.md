# xsh

xsh is a small Unix-like shell written in C.  
It started as an implementation based on a tutorial article and is being used as a foundation for experimentation and future extensions.

The project focuses on understanding how a basic shell works internally, including parsing input, handling built-in commands, and executing external programs.

## Overview

The shell is structured into small, focused modules:

- input parsing and tokenization
- built-in command handling
- command execution
- configuration and shared state

The codebase is organized to make it easy to extend the shell with new features and built-ins over time.

## Building and running

Clone the repository and build using `make`:

```bash
git clone https://github.com/geovannewashington/xsh.git
cd xsh
make
```

Run the shell:

```bash
./xsh
```

## Project structure

High-level documentation about the internal layout is available in `STRUCTURE.md.`
Planned features and improvements are tracked in `TODO.md.`

Basic tests are located in the `tests/` directory.

## Notes

This project is intentionally minimal and educational.
Its purpose is to serve as a base for experimenting with shell features, C programming patterns, and Unix process management.
