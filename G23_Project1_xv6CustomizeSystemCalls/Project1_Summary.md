# Project 1: xv6 System Call Customization

## 🎯 Motive
Operating Systems are not magic; they are massive C programs. The goal of this project is to cross the boundary between "User Space" and "Kernel Space". By hacking the MIT xv6 OS (a UNIX clone), we will hardwire our own custom capabilities directly into its core

## 📝 Project Summary
* **Environment:** Modify the xv6 operating system
* **Core Task:** Analyze the existing implementation of system calls and write new ones (or modify existing ones)
* **Scope:** Implement at least five functionalities. These must relate to core OS concepts like process creation, inter-process communication (IPC), threads, locks, or signals
* **Proof of Concept:** Demonstrate that these new system calls work by writing a custom user program within xv6 that incorporates them

## 📚 What to Learn (The Curriculum)
1. **The xv6 Architecture:** Understand the file structure, specifically the separation between user-space (`user/`) and kernel-space (`kernel/`).
2. **The "Trap" Mechanism:** Learn how software interrupts (traps) trigger system calls and securely transition execution into the kernel.
3. **System Call Wiring (The 5 Files):** * `syscall.h` (Assign unique syscall numbers)
   * `syscall.c` (Add function pointers to the syscall array)
   * `sysproc.c` / `sysfile.c` (Write the actual C logic)
   * `usys.pl` & `user.h` (Create the user-facing interface)
4. **Internal OS Management:** Learn how xv6 manages the `proc` structure for process creation and IPC.

## ✅ Deliverables Checklist
- [ ] Push modified xv6 source code to the `G23_Project1_xv6CustomizeSystemCalls` subfolder
- [ ] Write proper documentation detailing the work done on the 7 system calls
- [ ] Include screenshots of the user program executing the custom system calls in the documentation file