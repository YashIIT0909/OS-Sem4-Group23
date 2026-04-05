#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void)
{
    int count = getreadcount();
    printf("Total read() system calls so far: %d\n", count);
    exit(0);
}