#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT 1024
#define MAX_ARGS 100

int main() {
    char input[MAX_INPUT];
    char *args[MAX_ARGS];
    
    printf("========================================\n");
    printf("  Welcome to Dinesh's Custom OS Shell   \n");
    printf("========================================\n");

    // The Infinite Shell Loop
    while (1) {
        // 1. Print the prompt
        printf("dinesh-sh$ ");
        fflush(stdout); // Ensure prompt prints immediately

        // 2. Read user input
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break; // Exit if Ctrl+D is pressed
        }

        // Remove the trailing newline character that fgets adds
        input[strcspn(input, "\n")] = 0;

        // If the user just pressed Enter, do nothing and loop again
        if (strlen(input) == 0) {
            continue;
        }

        // 3. Parse the input into arguments separated by spaces
        int i = 0;
        args[i] = strtok(input, " ");
        
        // If the user typed "exit", break the infinite loop to close the shell
        if (args[0] != NULL && strcmp(args[0], "exit") == 0) {
            printf("Exiting Dinesh's Shell. Goodbye!\n");
            break;
        }

        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " ");
        }

        // 4. Fork and Execute
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
        } 
        else if (pid == 0) {
            // --- CHILD PROCESS ---
            // execvp replaces the child process with the command you typed
            if (execvp(args[0], args) < 0) {
                printf("Command not found: %s\n", args[0]);
                exit(1); // Kill the child if the command doesn't exist
            }
        } 
        else {
            // --- PARENT PROCESS (The Shell) ---
            // The shell waits for the child command to finish before printing the prompt again
            waitpid(pid, NULL, 0);
        }
    }

    return 0;
}