/*
 * custom_wc.c
 * Author  : Sankar (Section 2 - G23 Project 2)
 * Purpose : Count the total number of characters, words, and lines in a file.
 * Usage   : ./custom_wc <filename>
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* ANSI colour codes for a nicer terminal output */
#define COLOUR_RED     "\033[1;31m"
#define COLOUR_GREEN   "\033[1;32m"
#define COLOUR_CYAN    "\033[1;36m"
#define COLOUR_YELLOW  "\033[1;33m"
#define COLOUR_RESET   "\033[0m"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr,
                COLOUR_YELLOW "Usage: %s <filename>\n" COLOUR_RESET,
                argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr,
                COLOUR_RED "Error: Cannot open file '%s'\n" COLOUR_RESET,
                filename);
        return EXIT_FAILURE;
    }

    int chars = 0;
    int words = 0;
    int lines = 0;
    int in_word = 0;
    int ch;

    while ((ch = fgetc(fp)) != EOF) {
        chars++;

        if (ch == '\n') {
            lines++;
        }

        if (isspace(ch)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            words++;
        }
    }

    fclose(fp);

    printf(COLOUR_CYAN "-------------------------------------------\n" COLOUR_RESET);
    printf(COLOUR_GREEN "File: " COLOUR_RESET "%s\n", filename);
    printf(COLOUR_CYAN "Lines : " COLOUR_YELLOW "%d\n" COLOUR_RESET, lines);
    printf(COLOUR_CYAN "Words : " COLOUR_YELLOW "%d\n" COLOUR_RESET, words);
    printf(COLOUR_CYAN "Chars : " COLOUR_YELLOW "%d\n" COLOUR_RESET, chars);
    printf(COLOUR_CYAN "-------------------------------------------\n" COLOUR_RESET);

    return EXIT_SUCCESS;
}
