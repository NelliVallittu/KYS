#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 500

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("my-zip: file1 [file2 ...]\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("my-zip: cannot open file\n");
            exit(1);
        }

        int count = 0;
        char currentChar, prevChar;
        int firstChar = 1;

        char buffer[MAX];
        while (fgets(buffer, MAX, fp) != NULL) {
            for (int j = 0; j < strlen(buffer); j++) {
                currentChar = buffer[j];
                
                if (firstChar) {
					// ensimmäinen merkki tallennetaan
                    prevChar = currentChar;
                    count = 1;
                    firstChar = 0;
                } else if (currentChar == prevChar) {
					//sama merkki jatkuu
                    count++;
                } else {
					//tallennetaan tulos
                    fwrite(&count, sizeof(int), 1, stdout);
                    fwrite(&prevChar, sizeof(char), 1, stdout);
					//aloitetaan uuden merkin laskenta
                    prevChar = currentChar;
                    count = 1;
                }
            }
        }
		// tallennetaan viimeinen merkki
        if (count > 0) {
            fwrite(&count, sizeof(int), 1, stdout);
            fwrite(&prevChar, sizeof(char), 1, stdout);
        }

        fclose(fp);
    }

    return 0;
}
