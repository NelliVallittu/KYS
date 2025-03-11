#include <stdio.h>
#include <stdlib.h>

// funktio purkaa pakatun tiedoston
void decompress(FILE *input) {
    int count;
    char character;

    while (fread(&count, sizeof(int), 1, input) == 1) { // luetaan toistomäärä
        fread(&character, sizeof(char), 1, input); // luetaan merkki
        
        for (int i = 0; i < count; i++) { //tulostetaan merkki (count) kertaa
            putchar(character);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("my-unzip: file1 [file2 ...]\n");
        return 1;
    }
	//käsitellään kaikki annetut tiedostot
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "rb");
        if (!fp) {
            printf("my-unzip: cannot open file %s\n", argv[i]);
            return 1;
        }

        decompress(fp);
        fclose(fp);
    }

    return 0;
}
