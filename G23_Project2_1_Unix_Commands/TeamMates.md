# Project 2: Custom UNIX Shell & Utilities - Team Action Plan

Welcome to Project 2. For this project, we are building a custom UNIX-like terminal shell and our own lightweight versions of 7 standard commands entirely in C. 

**Important:** We are NOT using xv6 for this. These are standard C programs compiled using `gcc` on Ubuntu.

## 🏗️ The Architecture
We are building independent executable files for each command (e.g., `custom_cat`, `custom_ls`). 
The **Main Shell** will run an infinite `while(1)` loop, read the user's input, and use the `fork()`, `exec()`, and `wait()` system calls to run our custom executables.

---

## 📸 Step 1: Screenshots & Proof (CRITICAL)
Just like Project 1, we must prove our code works. 
1. When your assigned commands are finished, run them inside our Custom Shell.
2. Take a screenshot of the terminal showing the successful execution.
3. Save it in the `Screenshots/` folder inside the Project 2 directory.
4. **Naming Convention:** Use your name and the command name (e.g., `sankar_custom_grep.png`).

---

## ⚔️ Step 2: Task Distribution

Everyone is responsible for writing the pure C code for their assigned utilities. 

### 👤 Section 1: The Core Engine (Assigned to: Dinesh)
* **The Main Shell (`shell.c`):** Build the master program that prints the prompt (`dinesh-sh$ `), parses user input, and uses `fork/exec` to launch the other commands.
* **Utility 1 (`custom_cat.c`):** Reads a file and prints its contents to the terminal.
* **Infrastructure:** Set up the `Makefile` to compile all the C files easily.

### 👤 Section 2: File Analysis (Assigned to: Sankar)
* **Utility 2 (`custom_grep.c`):** Opens a file, reads it line-by-line, and prints only the lines that contain a specific search word.
* **Utility 3 (`custom_wc.c`):** Opens a file and counts the total number of characters, words, and lines inside it.

### 👤 Section 3: File Operations (Assigned to: Yash Patidhar)
* **Utility 4 (`custom_cp.c`):** Copies the contents of a source file into a new destination file.
* **Utility 5 (`custom_rm.c`):** Uses the `unlink()` system call to permanently delete a file.

### 👤 Section 4: Directory Operations & QA (Assigned to: Yash Agarwal)
* **Utility 6 (`custom_ls.c`):** Opens the current directory and prints the names of all files inside it (using `<dirent.h>`).
* **Utility 7 (`custom_mv.c`):** Renames a file or moves it to a different location.
* **Documentation (`README.md`):** Write the final instructions on how to compile and run our shell.