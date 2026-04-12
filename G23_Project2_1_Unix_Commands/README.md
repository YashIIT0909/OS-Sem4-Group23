# Project 2: UNIX-like Utilities in C

## Overview
This project implements a mini suite of UNIX-like command-line utilities in C, along with a custom shell to execute them. The goal is to practice process control, file handling, directory operations, and text processing using core Linux system calls and standard C APIs.

Implemented commands:
- shell
- custom_cat
- custom_ls
- custom_mv
- custom_grep
- custom_wc
- custom_cp
- custom_rm

## Project Structure
- commands/: C source files for all utilities
- Screenshots/: terminal output evidence for each command
- test.txt: sample input file for testing
- shell, custom_cat, custom_ls, custom_mv: compiled binaries (already present)

## Team Contribution Mapping
- Custom Shell (shell): Dinesh
- Custom Cat (custom_cat): Dinesh
- Custom LS (custom_ls): Yash Agarwal
- Custom MV (custom_mv): Yash Agarwal
- Custom Grep (custom_grep): Sankar
- Custom WC (custom_wc): Sankar
- Custom CP (custom_cp): Yash Patidar
- Custom RM (custom_rm): Yash Patidar

## Source Files
- commands/shell.c
- commands/custom_cat.c
- commands/custom_ls.c
- commands/custom_mv.c
- commands/custom_grep.c
- commands/custom_wc.c
- commands/custom_cp.c
- commands/custom_rm.c

## Prerequisites
- Linux environment
- GCC compiler
- Standard C libraries available on most Linux distributions

## Build Instructions
Run these commands from the project folder:

```bash
gcc commands/shell.c -o shell
gcc commands/custom_cat.c -o custom_cat
gcc commands/custom_ls.c -o custom_ls
gcc commands/custom_mv.c -o custom_mv
gcc commands/custom_grep.c -o custom_grep
gcc commands/custom_wc.c -o custom_wc
gcc commands/custom_cp.c -o custom_cp
gcc commands/custom_rm.c -o custom_rm
```

Optional one-liner build:

```bash
gcc commands/shell.c -o shell && \
gcc commands/custom_cat.c -o custom_cat && \
gcc commands/custom_ls.c -o custom_ls && \
gcc commands/custom_mv.c -o custom_mv && \
gcc commands/custom_grep.c -o custom_grep && \
gcc commands/custom_wc.c -o custom_wc && \
gcc commands/custom_cp.c -o custom_cp && \
gcc commands/custom_rm.c -o custom_rm
```

## How to Run

### 1. Start the custom shell
```bash
./shell
```

Type commands at the prompt and use `exit` to quit.

### 2. Run commands directly

#### custom_cat
```bash
./custom_cat test.txt
```
Prints file content to stdout.

#### custom_ls
```bash
./custom_ls
./custom_ls -l
./custom_ls /path/to/dir
```
Lists directory entries, with optional long format (`-l`) and color output.

#### custom_mv
```bash
./custom_mv oldname.txt newname.txt
./custom_mv file.txt target_directory/
```
Renames or moves files/directories using `rename()`.

#### custom_grep
```bash
./custom_grep pattern test.txt
```
Searches for matching lines and prints line numbers with highlighted matches.

#### custom_wc
```bash
./custom_wc test.txt
```
Prints line, word, and character counts.

#### custom_cp
```bash
./custom_cp source.txt copy.txt
```
Copies file contents from source to destination.

#### custom_rm
```bash
./custom_rm copy.txt
```
Deletes a file using `unlink()`.

## Command Summary Table
| Command | Purpose | Usage |
|---|---|---|
| shell | Interactive command interpreter | `./shell` |
| custom_cat | Display file contents | `./custom_cat <filename>` |
| custom_ls | List directory contents | `./custom_ls [-l] [path]` |
| custom_mv | Move/rename file or directory | `./custom_mv <source> <destination>` |
| custom_grep | Search pattern in file | `./custom_grep <pattern> <filename>` |
| custom_wc | Count lines, words, characters | `./custom_wc <filename>` |
| custom_cp | Copy file | `./custom_cp <source> <destination>` |
| custom_rm | Remove file | `./custom_rm <filename>` |

## Screenshots
- Shell: Screenshots/dinesh_shell_terminal.png
- custom_cat: Screenshots/dinesh_cat_terminal.png
- custom_ls: Screenshots/yash_agarwal_ls_terminal.png
- custom_mv: Screenshots/yash_agarwal_mv_terminal.png
- custom_grep: Screenshots/sankar_grep_terminal.png
- custom_wc: Screenshots/sankar_wc_terminal.png
- custom_cp: Screenshots/yash_patidar_cp_terminal.png
- custom_rm: Screenshots/yash_patidar_rm_terminal.png

## Notes and Limitations
- Commands are intentionally simplified versions of standard UNIX utilities.
- Feature coverage is basic (for example, no recursive delete in custom_rm and no multiple-file support in custom_cat).
- The shell uses `fork()` + `execvp()` and waits for each child process to finish.

