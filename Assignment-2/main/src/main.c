#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

#define MAX_NAME_BUFFER_SIZE 10000

int get_name_index() {
    static int count = 0;

    if (count >= MAX_NAME_BUFFER_SIZE) {
        printf("WARNING: Max size of name allocation buffer reached\n");
    }

    return count++;
}

char* NAME_BUFFER[MAX_NAME_BUFFER_SIZE];

void free_name_buffer() {
    int name_allocation_count = get_name_index();

    // printf("Freeing %d name allocations\n", name_allocation_count);

    for (int i = name_allocation_count - 1; i >= 0; --i) {
        free(NAME_BUFFER[i]);
    }
}

// You are allowed to change anything about this function to fix it
int main() {
    char* commandBuffer = (char*)malloc(sizeof(char) * 20);

    Tree* tree = tree_create();

    for (;;) {
        fgets(commandBuffer, 20, stdin);

        // Quit on EOF or 'q'
        if (feof(stdin) || *commandBuffer == 'q') {
            break;
        }

        tree = handleString(commandBuffer, tree);
    };

    tree_delete(tree);
    free(commandBuffer);
    free_name_buffer();

    return 0;
}

/**
 * Handle a command entered into the program
 *
 * You are allowed to change anything about this function to fix it
 * @param command The command string to handle
 */
Tree* handleString(char command[], Tree* tree) {
    if (command == NULL) {
        fprintf(stderr, "Invalid command; null pointer\n");
        return tree;
    }

    switch (command[0]) {
        case 'i':
            insert(command, tree);
            break;
        case 'e':
            erase(command, tree);
            break;
        case 'c':
            check(command, tree);
            break;
        case 'p':
            tree_print(tree, 1);
            break;
        case 'x':
            tree_delete(tree);
            return tree_create();
        default:
            fprintf(stderr, "Invalid command string: %s\n", command);
            break;
    }

    return tree;
}

// You are allowed to change anything about this function to tix it
Tree* insert(char* command, Tree* tree) {
    int age;
    char* name = malloc(sizeof(char) * 20);

    if (2 != sscanf(command, "i %d %19s", &age, name)) {
        fprintf(
            stderr,
            "Failed to parse insert command: not enough parameters filled\n");
        free(name);
        return NULL;
    }

    NAME_BUFFER[get_name_index()] = name;

    if (tree == NULL) {
        tree = tree_create();
    }

    tree_insert(tree, age, name);
    return tree;
}

// You are allowed to change anything about this function to fix it
void erase(char* command, Tree* tree) {
    int age;
    char* name = malloc(sizeof(char) * 20);

    if (2 != sscanf(command, "e %d %19s", &age, name)) {
        fprintf(
            stderr,
            "Failed to parse erase command: not enough parameters filled\n");
        free(name);
        return;
    }
    tree_erase(tree, age, name);
}

// You are allowed to change anything about this function to fix it
void check(char* command, Tree* tree) {
    int age;
    char* name = malloc(sizeof(char) * 20);

    if (2 != sscanf(command, "c %d %19s", &age, name)) {
        fprintf(stderr, "Failed to parse check command\n");
        free(name);
        return;
    }

    Node* result = tree_find(tree, age, name);
    if (result) {
        printf("y\n");
    } else {
        printf("n\n");
    }
}
