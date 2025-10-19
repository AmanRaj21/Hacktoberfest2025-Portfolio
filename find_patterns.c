#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_TEXT 5000
#define MAX_PATTERN 256

void find_patterns(const char *text, const char *pattern) {
    regex_t regex;
    regmatch_t match[1];

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex pattern.\n");
        exit(1);
    }

    const char *ptr = text;
    int count = 0;

    while (regexec(&regex, ptr, 1, match, 0) == 0) {
        int start = match[0].rm_so;
        int end = match[0].rm_eo;

        printf("%.*s\n", end - start, ptr + start);

        ptr += end; // Move forward
        count++;
    }

    if (count == 0)
        printf("No matches found.\n");

    regfree(&regex);
}

int main() {
    char text[MAX_TEXT];
    char pattern[MAX_PATTERN];
    char choice;

    printf("Text Pattern Finder\n");
    printf("==================\n");
    printf("Do you want to read text from a file? (y/n): ");
    scanf(" %c", &choice);
    getchar(); // Consume newline

    if (choice == 'y' || choice == 'Y') {
        char filename[256];
        printf("Enter filename: ");
        fgets(filename, sizeof(filename), stdin);
        filename[strcspn(filename, "\n")] = 0; // Remove newline

        FILE *file = fopen(filename, "r");
        if (!file) {
            perror("File open error");
            return 1;
        }

        fread(text, sizeof(char), MAX_TEXT, file);
        fclose(file);
    } else {
        printf("Enter text: ");
        fgets(text, sizeof(text), stdin);
        text[strcspn(text, "\n")] = 0; // Remove newline
    }

    printf("Enter regex pattern: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = 0; // Remove newline

    printf("\nMatches found:\n");
    printf("----------------\n");
    find_patterns(text, pattern);

    return 0;
}
