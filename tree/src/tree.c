#include "tree.h"

//
void replace_node(Node* erased_node, Node* replacement) {
    if (!erased_node->parent) return;

    if (erased_node->parent->left == erased_node)
        erased_node->parent->left = replacement;
    else
        erased_node->parent->right = replacement;

    if (replacement) replacement->parent = erased_node->parent;
}

void delete_node(Node* node) {
    printf("Deleting node with name %s\n", node->name);

    // TODO: Should we delete name here?? If the name is passed as a literal
    // we get double free...
    // free(node->name);
    free(node);
}

/**
 * Please correct the contents of this file to make sure all functions here do
 * what they are supposed to do if you find that they do not work as expected.
 */

// Tree function: you are allowed to change the contents, but not the method
// signature
Tree* tree_create() {
    Tree* tree = malloc(sizeof(Tree));
    tree->root = NULL;

    return tree;
}

// Helper function: you are allowed to change this to your preferences
void tree_node_delete(Node* node) {
    if (node == NULL) return;

    tree_node_delete(node->left);
    tree_node_delete(node->right);

    delete_node(node);
}

// Tree function: you are allowed to change the contents, but not the method
// signature
void tree_delete(Tree* tree) {
    tree_node_delete(tree->root);

    free(tree);
}

Node* create_node(int age, char* name, Node* parent) {
    Node* node = malloc(sizeof(Node));
    node->age = age;
    node->name = name;

    node->left = NULL;
    node->right = NULL;
    node->parent = parent;

    return node;
}

// Helper function: you are allowed to change this to your preferences
void node_insert(Node* node, int age, char* name) {
    if (age <= node->age) {
        if (node->left == NULL) {
            node->left = create_node(age, name, node);
        } else {
            node_insert(node->left, age, name);
        }
    } else {
        if (node->right == NULL) {
            node->right = create_node(age, name, node);
        } else {
            node_insert(node->right, age, name);
        }
    }
}

// Tree function: you are allowed to change the contents, but not the method
// signature
void tree_insert(Tree* tree, int age, char* name) {
    if (tree->root == NULL) {
        tree->root = create_node(age, name, NULL);

    } else {
        node_insert(tree->root, age, name);
    }
}

Node* find_max_sub_node(Node* node) {
    if (!node->right) return node;
    return find_max_sub_node(node->right);
}

Node* node_erase(Node* data) {
    Node* new_top = NULL;

    if (!data->left && !data->right) {
        replace_node(data, NULL);
        delete_node(data);
    }

    else if (data->left && !data->right) {
        replace_node(data, data->left);
        new_top = data->left;
        delete_node(data);
    }

    else if (!data->left && data->right) {
        replace_node(data, data->right);
        new_top = data->right;
        delete_node(data);
    }

    else {
        Node* replacement = find_max_sub_node(data->left);

        char* tmp = data->name;

        data->name = replacement->name;
        data->age = replacement->age;

        replacement->name = tmp;

        new_top = data;

        node_erase(replacement);
    }

    return new_top;
}

// Tree function: you are allowed to change the contents, but not the method
// signature
void tree_erase(Tree* tree, int age, char* name) {
    Node* data = tree_find(tree, age, name);
    if (!data) return;

    if (!data->parent && !data->left && !data->right) {
        tree->root = NULL;
    }

    if (data == tree->root) {
        Node* new_top = node_erase(data);
        tree->root = new_top;

    } else {
        node_erase(data);
    }
}

// Helper function: you are allowed to change this to your preferences
void tree_print_node(Node* node) {
    if (node == NULL) {
        printf("null");
        return;
    }

    printf("[");
    printf("{\"%d\":\"%s\"},", node->age, node->name);
    tree_print_node(node->left);
    printf(",");
    tree_print_node(node->right);
    printf("]");
}

// Tree function: you are allowed to change the contents, but not the method
// signature
void tree_print(Tree* tree, int printNewline) {
    if (tree == NULL) {
        printf("null");
        return;
    }

    tree_print_node(tree->root);

    if (printNewline) {
        printf("\n");
    }
}

// Helper function: you are allowed to change this to your preferences
Node* node_find(Node* node, int age, char* name) {
    if (!node) {
        return NULL;
    }

    if (node->age == age && strcmp(node->name, name) == 0) {
        return node;
    }

    if (age <= node->age) {
        return node_find(node->left, age, name);
    } else {
        return node_find(node->right, age, name);
    }
}

// Tree function: you are allowed to change the contents, but not the method
// signature
Node* tree_find(Tree* tree, int age, char* name) {
    return node_find(tree->root, age, name);
}
