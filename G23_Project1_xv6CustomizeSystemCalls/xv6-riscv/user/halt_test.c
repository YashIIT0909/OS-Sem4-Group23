#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
    printf("Shutting down the OS...\n");
    halt();
    exit(0);
}