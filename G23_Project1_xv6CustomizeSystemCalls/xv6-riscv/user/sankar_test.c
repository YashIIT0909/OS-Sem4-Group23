#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  printf("--- Sankar Section 2 Tests ---\n\n");

  printf("Testing sys_ps():\n");
  ps();
  printf("-----------------------------\n\n");

  int pid = getpid();
  printf("Testing sys_getprocinfo() for current PID (%d):\n", pid);
  if(getprocinfo(pid) < 0){
    printf("getprocinfo failed\n");
  }

  printf("\nTesting sys_getprocinfo() for non-existent PID (999):\n");
  if(getprocinfo(999) < 0){
    printf("Expected failure occurred\n");
  }

  printf("\n--- Test Complete ---\n");
  exit(0);
}
