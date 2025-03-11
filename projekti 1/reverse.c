#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFFER_SIZE 1024


typedef struct Node {
    char *line;
    struct Node *next;
} Node;


void print_usage() {
    fprintf(stderr, "usage: reverse <input> <output>\n");
    exit(1);
}


void handle_malloc_error() {
    fprintf(stderr, "malloc failed\n");
    exit(1);
}


Node *create_node(char *line) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) handle_malloc_error();
    new_node->line = line;
    new_node->next = NULL;
    return new_node;
}


void push(Node **head, char *line) {
    Node *new_node = create_node(line);
    new_node->next = *head;
    *head = new_node;
}


void free_list(Node *head) {
    Node *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp->line);
        free(temp);
    }
}


int main(int argc, char *argv[]) {
    FILE *input_file = stdin;
    FILE *output_file = stdout;
    Node *lines = NULL;


    if (argc > 3) {
        print_usage();
    }


    if (argc >= 2) {
        input_file = fopen(argv[1], "r");
        if (!input_file) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
    }


    if (argc == 3) {
        if (strcmp(argv[1], argv[2]) == 0) {
            fprintf(stderr, "Input and output file must differ\n");
            exit(1);
        }


        output_file = fopen(argv[2], "w");
        if (!output_file) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
            exit(1);
        }
    }


    char *buffer = NULL;
    size_t len = 0;
    ssize_t read;


    while ((read = getline(&buffer, &len, input_file)) != -1) {
        char *line_copy = strdup(buffer);
        if (!line_copy) handle_malloc_error();
        push(&lines, line_copy);
    }
    free(buffer);


Node *current = lines;
while (current) {
    fprintf(output_file, "%s", current->line);


    size_t len = strlen(current->line);
    if (len > 0 && current->line[len - 1] != '\n') {
        fprintf(output_file, "\n");
    }
   
    current = current->next;
}


    free_list(lines);
    if (input_file != stdin) fclose(input_file);
    if (output_file != stdout) fclose(output_file);


    return 0;
}
