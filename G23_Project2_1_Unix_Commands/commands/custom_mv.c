#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *src = argv[1];
    char *dest = argv[2];
    char dest_path[1024];
    struct stat dest_stat;

    // Check if the destination is an existing directory
    if (stat(dest, &dest_stat) == 0 && S_ISDIR(dest_stat.st_mode)) {
        // Destination is a directory. Construct: dest_dir/source_basename
        char src_copy[1024];
        strncpy(src_copy, src, sizeof(src_copy) - 1);
        src_copy[sizeof(src_copy) - 1] = '\0';
        
        char *base_name = basename(src_copy);
        snprintf(dest_path, sizeof(dest_path), "%s/%s", dest, base_name);
    } else {
        // Destination is a direct file path
        strncpy(dest_path, dest, sizeof(dest_path) - 1);
        dest_path[sizeof(dest_path) - 1] = '\0';
    }

    // Rename system call handles moving within the same filesystem
    if (rename(src, dest_path) != 0) {
        perror("custom_mv: Error");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
