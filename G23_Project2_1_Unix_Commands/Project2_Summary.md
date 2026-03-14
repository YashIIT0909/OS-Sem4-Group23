# Project 2: Custom UNIX Shell & Utilities

## 🎯 Motive
To demystify how command-line tools work by building lightweight versions of them from scratch[cite: 34]. This project will solidify our understanding of standard C libraries, file I/O operations, and process management system calls (`fork`, `exec`, `wait`).

## 📝 Project Summary
* **Core Task:** Develop a series of simplified UNIX-like utilities from scratch in C[cite: 34, 46].
* **The Utilities:** Implement custom versions of `ls`, `cat`, `grep`, `wc`, `cp`, `mv`, and `rm`[cite: 38, 39, 40, 41, 42, 43, 44].
* **Naming Convention:** Use unique names (e.g., `custom_cat`, `custom_ls`) to avoid confusion with standard UNIX commands[cite: 36, 37].
* **The Shell:** Build a main UNIX-like shell program to act as the interface for running these other custom commands[cite: 46].

## 📚 What to Learn (The Curriculum)
1. **File I/O (`cat`, `cp`, `wc`):** Master standard C functions like `fopen()`, `fread()`, `fwrite()`, `fgetc()`, and `fclose()`.
2. **Directory Traversal (`ls`, `rm`, `mv`):** Learn to use the `<dirent.h>` and `<sys/stat.h>` libraries (`opendir()`, `readdir()`, `rename()`).
3. **String Manipulation (`grep`):** Get comfortable reading files line-by-line (`fgets()`) and searching for patterns (`strstr()`).
4. **The Process Engine (The Shell):** Build an infinite `while(1)` loop that reads user input, calls `fork()` to create a child process, uses `exec()` to run the custom utility, and uses `wait()` in the parent process to keep the shell prompt stable.

## ✅ Deliverables Checklist
- [ ] Push all C source files (the utilities and the main shell) to the `Groupname_Project2_projectno` subfolder[cite: 9].
- [ ] Write a proper `makefile` to compile the shell and all commands easily[cite: 47].
- [ ] Write a `Readme` file explaining how to compile and run the shell[cite: 47].
- [ ] Include screenshots of the custom shell executing the utilities in the documentation file[cite: 48].