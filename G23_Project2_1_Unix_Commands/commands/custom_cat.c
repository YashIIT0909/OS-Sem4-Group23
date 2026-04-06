#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // If no file is specified, we can't do anything
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char ch;
    // Read character by character until End Of File (EOF)
    printf("New Command @Dinesh: ");
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
    return 0;
}