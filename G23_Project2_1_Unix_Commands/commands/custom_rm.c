#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: custom_rm <filename>\n");
        return 1;
    }

    if (unlink(argv[1]) == 0) {
        printf("File deleted successfully: %s\n", argv[1]);
        return 0;
    } else {
        printf("Error: Cannot delete %s (maybe file does not exist or permission issue)\n", argv[1]);
        return 1;
    }
}