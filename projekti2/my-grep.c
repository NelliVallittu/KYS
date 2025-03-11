#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// etsitään hakusanaa annetusta tiedostosta
void search_in_file(const char *search_term, FILE *file) {
    char *line = NULL;
    size_t len = 0;
    
    while (getline(&line, &len, file) != -1) {
        if (strstr(line, search_term) != NULL) { // etsitään osumaa riviltä
            printf("%s", line);
        }
    }
    
    free(line); // vapauta muisti
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "my-grep: searchterm [file ...]\n");
        return 1;
    }
    
    const char *search_term = argv[1];
    
    if (argc == 2) {
        // luetaan syötteestä
        search_in_file(search_term, stdin);
    } else {
        // käsitellään jokainen annettu tiedosto
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
