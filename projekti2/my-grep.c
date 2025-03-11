#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void search_in_file(const char *search_term, FILE *file) {
    char *line = NULL;
    size_t len = 0;
    
    while (getline(&line, &len, file) != -1) {
        if (strstr(line, search_term) != NULL) { // Case-sensitive match
            printf("%s", line);
        }
    }
    
    free(line); // Free the memory allocated by getline
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "my-grep: searchterm [file ...]\n");
        return 1;
    }
    
    const char *search_term = argv[1];
    
    if (argc == 2) {
        // No file arguments, read from standard input
        search_in_file(search_term, stdin);
    } else {
        // Loop through each file argument
        for (int i = 2; i < argc; i++) {
            FILE *file = fopen(argv[i], "r");
            if (file == NULL) {
                fprintf(stderr, "my-grep: cannot open file\n");
                return 1;
            }
            search_in_file(search_term, file);
            fclose(file);
        }
    }
    
    return 0;
}
