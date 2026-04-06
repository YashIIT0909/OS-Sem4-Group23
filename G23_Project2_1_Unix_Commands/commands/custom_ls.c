#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define COLOR_RESET "\033[0m"
#define COLOR_DIR "\033[1;34m"  // Bold Blue
#define COLOR_EXEC "\033[1;32m" // Bold Green

void print_colored_name(const char *dir_path, const char *filename)
{
    struct stat file_stat;
    char full_path[1024];

    snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, filename);

    if (stat(full_path, &file_stat) == -1)
    {
        printf("%s", filename);
        return;
    }

    if (S_ISDIR(file_stat.st_mode))
    {
        printf("%s%s%s", COLOR_DIR, filename, COLOR_RESET);
    }
    else if (file_stat.st_mode & S_IXUSR)
    {
        printf("%s%s%s", COLOR_EXEC, filename, COLOR_RESET);
    }
    else
    {
        printf("%s", filename);
    }
}

void print_long_format(const char *dir_path, const char *filename)
{
    struct stat file_stat;
    char full_path[1024];

    // Construct full path for stat()
    snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, filename);

    // Get file info
    if (stat(full_path, &file_stat) == -1)
    {
        return; // silently skip if stat fails
    }

    // Print File Type
    printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");

    // Print Permissions
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");

    // Number of links
    printf(" %lu", (unsigned long)file_stat.st_nlink);

    // Owner and Group
    struct passwd *pw = getpwuid(file_stat.st_uid);
    struct group *gr = getgrgid(file_stat.st_gid);
    printf(" %s %s", pw ? pw->pw_name : "unknown", gr ? gr->gr_name : "unknown");

    // File Size
    printf(" %8ld", (long)file_stat.st_size);

    // Last modified time
    char time_str[20];
    struct tm *tm_info = localtime(&file_stat.st_mtime);
    strftime(time_str, sizeof(time_str), "%b %d %H:%M", tm_info);
    printf(" %s", time_str);

    // File name
    printf(" ");
    print_colored_name(dir_path, filename);
    printf("\n");
}

int main(int argc, char *argv[])
{
    struct dirent *dir_entry;
    DIR *directory;
    const char *path = "."; // Default directory
    int is_long_format = 0;

    // Parse arguments
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-l") == 0)
        {
            is_long_format = 1;
        }
        else
        {
            path = argv[i];
        }
    }

    // Attempt to open directory
    directory = opendir(path);
    if (directory == NULL)
    {
        perror("custom_ls: Cannot open directory");
        return EXIT_FAILURE;
    }

    // Read directory entries
    while ((dir_entry = readdir(directory)) != NULL)
    {
        if (is_long_format)
        {
            print_long_format(path, dir_entry->d_name);
        }
        else
        {
            print_colored_name(path, dir_entry->d_name);
            printf("\n");
        }
    }

    closedir(directory);
    return EXIT_SUCCESS;
}
