// fopen, fgets, fclose
#include <stdio.h>
#include <stdlib.h>
#define MAX 500

int main(int argc, char *argv[]){

	if (argc < 2){
		exit(0);
	}
	
	int i = 1;

	while (i < argc){
		FILE *fp = fopen(argv[i], "r");
	
		if (fp == NULL){
			printf("my-cat: cannot open file");
			exit(1);
		}

		char buffer[MAX];

		while (fgets(buffer, MAX, fp) != NULL){
			printf("%s", buffer);
		}
		fclose(fp);
		printf("\n");
		i++;
	}

	return 0;
}