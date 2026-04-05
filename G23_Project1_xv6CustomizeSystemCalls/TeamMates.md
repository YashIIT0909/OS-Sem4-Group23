# Project 1: xv6 Custom System Calls - Team Action Plan

Welcome to Project 1. We are modifying the MIT xv6 operating system kernel to add at least 5 new custom system calls. 

To avoid Git conflicts with other work, **our official team codebase is on the `main`.**

## 📥 Step 1: How to get the code
Do not just run a standard `git clone`. You must pull our specific branch. Run this in your terminal:

```bash
# Clone ONLY the main branch
git clone <PASTE_OUR_GITHUB_REPO_URL_HERE>

# Go into the folder
cd xv6-riscv

# Test that your compiler works
make qemu
```
*(To exit xv6, press `Ctrl + A`, release, then press `X`)*.

---

## 🏗️ Step 2: How to add a System Call
To add your assigned system call to the OS, you must touch these 5 files. **Do not edit other people's files without communicating!**

1. `user/user.h`: Add your function prototype (e.g., `int my_syscall(void);`)
2. `user/usys.pl`: Add the assembly routing (e.g., `entry("my_syscall");`)
3. `kernel/syscall.h`: Define your unique ID number (e.g., `#define SYS_my_syscall 23`)
4. `kernel/syscall.c`: Add your function to the kernel's routing array.
5. `kernel/sysproc.c` (or `sysfile.c`): Write the actual C logic for your function.

---

## 📸 Step 3: Screenshots & Proof (CRITICAL)
The professor strictly requires proof of execution. Once your system call works:
1. Take a screenshot of the C code you wrote (e.g., your logic inside `sysproc.c`).
2. Take a screenshot of the QEMU terminal showing your test program running successfully.
3. Save them in the `Screenshots/` folder located in the project root.
4. **Naming Convention:** Use your name, the syscall name, and the type (code or terminal).
   * *Example:* `sankar_getprocinfo_code.png`
   * *Example:* `sankar_getprocinfo_terminal.png`

---

## ⚔️ Step 4: Task Distribution

### 👤 Section 1: The Foundation (Completed by: Dinesh)
* **Goal:** Set up the routing boilerplate for the team and implement system diagnostic calls.
* **Call 1: `sys_halt()`** - Shuts down the QEMU emulator.
* **Call 2: `sys_getreadcount()`** - Returns the global tally of how many times `read()` was called.

### 👤 Section 2: The Process Inspector (Assigned to: Sankar)
* **Goal:** Implement system calls that retrieve information about active processes. 
* **Call 3: `sys_getprocinfo()`** - Takes a PID and returns basic info about that specific process.
* **Call 4: `sys_ps()`** - Iterates through the kernel's process table and prints all active processes.
* *Files to modify:* `kernel/sysproc.c` and `kernel/proc.c`

### 👤 Section 3: The Hardware Scout (Assigned to: Yash Patidhar)
* **Goal:** Implement system calls that retrieve hardware and memory constraints.
* **Call 5: `sys_getfreemem()`** - Calculates how many bytes of free RAM are left in the system's memory allocator.
* **Call 6: `sys_getopenfiles()`** - Returns the number of files the currently running process has open.
* *Files to modify:* `kernel/sysproc.c`, `kernel/kalloc.c`, and `kernel/file.c`

### 👤 Section 4: QA & Controller (Assigned to: Yash Agarwal)
* **Goal:** Implement process modification and write the final testing application.
* **Call 7: `sys_setpriority()`** - Allows a user to change a process's priority.
* **The User App (`testapp.c`):** Write the user-space C program that calls and tests EVERY system call made by the team. You are responsible for executing the final run and capturing the master screenshots for the final report.
* *Files to modify:* `kernel/sysproc.c`, `user/testapp.c`, `Makefile`
