// fopen, fgets, fclose
#include <stdio.h>
#include <stdlib.h>

#define MAX 500

int main(int argc, char *argv[]){

	if (argc < 2){
		exit(0); // poistu jos ei tietoja annettu
	}
	
	int i = 1;

	while (i < argc){
		FILE *fp = fopen(argv[i], "r");
	
		if (fp == NULL){
			printf("my-cat: cannot open file");
			exit(1);
		}

		char buffer[MAX];

		//luetaan ja tulostetaan tiedoston sisältö
		while (fgets(buffer, MAX, fp) != NULL){
			printf("%s", buffer);
		}
		fclose(fp);
		printf("\n");
		i++;
	}

	return 0;
}