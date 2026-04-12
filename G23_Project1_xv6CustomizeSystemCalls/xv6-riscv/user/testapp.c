#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// --- Global variables for sigalarm test ---
volatile int alarm_count = 0;

void periodic()
{
    alarm_count = alarm_count + 1;
    printf("[Periodic Alarm] Triggered! count = %d\n", alarm_count);
    sigreturn();
}

void test_shared_memory()
{
    printf("\n==================================\n");
    printf("   TESTING SHARED MEMORY (shm_get)\n");
    printf("==================================\n");

    int parent_pid = getpid();
    printf("[Parent PID: %d] Starting tests.\n", parent_pid);

    void *shared_mem1 = shm_get(1234);
    if ((uint64)shared_mem1 == 0 || (uint64)shared_mem1 == -1)
    {
        printf("[Parent PID: %d] Failed to allocate shared memory!\n", parent_pid);
        return;
    }

    printf("[Parent PID: %d] Mapped shm(key=1234) successfully to virtual address: %p\n", parent_pid, shared_mem1);

    *((int *)shared_mem1) = 42;
    printf("[Parent PID: %d] Wrote value '42' to the shared memory slot.\n", parent_pid);
    printf("[Parent PID: %d] Forking child process...\n", parent_pid);

    int pid = fork();
    if (pid < 0)
    {
        printf("Fork failed!\n");
        return;
    }

    if (pid == 0)
    {
        int child_pid = getpid();
        printf("[Child PID: %d] Created successfully.\n", child_pid);

        // Child process sharing the memory key
        void *shared_mem2 = shm_get(1234);
        printf("[Child PID: %d] Mapped shm(key=1234) successfully to virtual address: %p\n", child_pid, shared_mem2);

        int val = *((int *)shared_mem2);
        printf("[Child PID: %d] Read value from shared memory: %d\n", child_pid, val);

        if (val == 42)
        {
            printf("\n=> test_shm_get: PASSED!\n\n");
        }
        else
        {
            printf("\n=> test_shm_get: FAILED! (Expected 42, got %d)\n\n", val);
        }

        printf("[Child PID: %d] Exiting child.\n", child_pid);
        exit(0); // Exit the child process properly so it doesn't continue the execution flow of the parent tests.
    }

    wait(0);
    printf("[Parent PID: %d] Child process exited. Continuing tests.\n", parent_pid);
}

void test_sigalarm_sys()
{
    int i;
    printf("\n==================================\n");
    printf("   TESTING SIGALARM & SIGRETURN   \n");
    printf("==================================\n");
    
    int main_pid = getpid();
    printf("[Main PID: %d] Starting test...\n", main_pid);
    printf("[Main PID: %d] Setting sigalarm interval to 2 ticks...\n", main_pid);
    
    // Reset global counter just in case
    alarm_count = 0;
    
    sigalarm(2, periodic);

    printf("[Main PID: %d] Entering wait-loop to trigger interrupts...\n", main_pid);
    for (i = 0; i < 500000000; i++)
    {
        if ((i % 100000) == 0)
            uptime(); // Make a syscall to spend time
            
        if (alarm_count >= 5)
        {
            printf("[Main PID: %d] Successfully intercepted %d alarms. Exiting loop.\n", main_pid, alarm_count);
            break; 
        }
    }

    printf("[Main PID: %d] Disabling sigalarm...\n", main_pid);
    sigalarm(0, 0);

    if (alarm_count >= 5)
    {
        printf("\n=> test_sigalarm: PASSED\n\n");
    }
    else
    {
        printf("\n=> test_sigalarm: FAILED\n\n");
    }
}

int main(int argc, char *argv[])
{
  printf("\n--- Starting Systems Calls Test App ---\n\n");

  // 1. Test getreadcount()
  int read_count = getreadcount();
  printf("[Test] getreadcount() returned: %d\n", read_count);

  int pipefd[2];
  if (pipe(pipefd) == 0) {
      write(pipefd[1], "a", 1);
      char buf[1];
      read(pipefd[0], buf, 1);
      close(pipefd[0]);
      close(pipefd[1]);
      int new_read_count = getreadcount();
      printf("[Test] getreadcount() after 1 read: %d\n", new_read_count);
  }

  // 2. Test getfreemem()
  int free_mem = getfreemem();
  printf("\n[Test] getfreemem() returned: %d bytes\n", free_mem);

  // 3. Test getopenfiles()
  int open_files = getopenfiles();
  printf("\n[Test] getopenfiles() initially returned: %d\n", open_files);
  int fd = open("dummy.txt", 0x202); 
  if (fd >= 0) {
      int new_open_files = getopenfiles();
      printf("[Test] getopenfiles() after opening 1 file: %d\n", new_open_files);
      close(fd);
  }

  // 4. Test ps()
  printf("\n[Test] Calling ps()...\n");
  ps();

  // 5. Test getprocinfo()
  int cur_pid = getpid();
  printf("\n[Test] Calling getprocinfo() for current pid (%d)...\n", cur_pid);
  int procs_info = getprocinfo(cur_pid);
  printf("[Test] getprocinfo() returned status/result: %d\n", procs_info);

  // 6. Test Shared Memory shm_get()
  test_shared_memory();

  // 7. Test Sigalarm & Sigreturn
  test_sigalarm_sys();

  // Note: Calling halt() will shut down the QEMU emulator immediately.
  printf("\n[Test] To test halt(), run it as a separate command or uncomment the code below.\n");
  // halt();

  printf("\n--- All tests completed! ---\n\n");

  exit(0);
}
