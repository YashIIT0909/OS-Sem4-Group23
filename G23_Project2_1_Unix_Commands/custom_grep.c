/*
 * custom_grep.c
 * Author  : Sankar (Section 2 - G23 Project 2)
 * Purpose : Search a file line-by-line for a given pattern and print
 *           every matching line with its line number.
 * Usage   : ./custom_grep <pattern> <filename>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ANSI colour codes for a nicer terminal output */
#define COLOUR_RED     "\033[1;31m"
#define COLOUR_GREEN   "\033[1;32m"
#define COLOUR_CYAN    "\033[1;36m"
#define COLOUR_YELLOW  "\033[1;33m"
#define COLOUR_RESET   "\033[0m"

#define MAX_LINE 4096

/*
 * highlight_match()
 * Walks through `line` and re-prints it, wrapping every occurrence of
 * `pattern` in red so the match is obvious in the terminal.
 */
static void highlight_match(const char *line, const char *pattern)
{
    size_t pat_len = strlen(pattern);
    const char *pos = line;
    const char *found;

    while ((found = strstr(pos, pattern)) != NULL) {
        /* Print the text before the match */
        fwrite(pos, 1, (size_t)(found - pos), stdout);
        /* Print the match in red */
        printf(COLOUR_RED "%s" COLOUR_RESET, pattern);
        pos = found + pat_len;
    }
    /* Print the remainder of the line */
    printf("%s", pos);
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr,
                COLOUR_YELLOW "Usage: %s <pattern> <filename>\n" COLOUR_RESET,
                argv[0]);
        return EXIT_FAILURE;
    }

    const char *pattern  = argv[1];
    const char *filename = argv[2];

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr,
                COLOUR_RED "Error: Cannot open file '%s'\n" COLOUR_RESET,
                filename);
        return EXIT_FAILURE;
    }

    printf(COLOUR_CYAN "Searching for \"" COLOUR_RESET
           COLOUR_GREEN "%s" COLOUR_RESET
           COLOUR_CYAN "\" in file: " COLOUR_RESET
           COLOUR_GREEN "%s\n" COLOUR_RESET,
           pattern, filename);
    printf(COLOUR_CYAN "-------------------------------------------\n" COLOUR_RESET);

    char   line[MAX_LINE];
    int    line_num    = 0;
    int    match_count = 0;

    while (fgets(line, sizeof(line), fp)) {
        line_num++;
        if (strstr(line, pattern)) {
            match_count++;
            printf(COLOUR_YELLOW "Line %4d | " COLOUR_RESET, line_num);
            highlight_match(line, pattern);
        }
    }

    fclose(fp);

    printf(COLOUR_CYAN "-------------------------------------------\n" COLOUR_RESET);
    if (match_count == 0) {
        printf(COLOUR_RED "No matches found for \"%s\"\n" COLOUR_RESET, pattern);
    } else {
        printf(COLOUR_GREEN "%d match(es) found across %d line(s) searched.\n"
               COLOUR_RESET, match_count, line_num);
    }

    return EXIT_SUCCESS;
}
