#include "tree.h"
#include <assert.h>
// Utility functions for AVL tree

// #define MAX(a, b)               \
//     ({                          \
//         __typeof__(a) _a = (a); \
//         __typeof__(b) _b = (b); \
//         _a > _b ? _a : _b;      \
//     })

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int get_height(Node* node) {
    if (node != NULL) return node->height;

    return 0;
}

int get_height_diff(Node* node) {
    if (node != NULL) {
        return get_height(node->left) - get_height(node->right);
    }

    return 0;
}

void set_height(Node* node, int height) {
    // printf("setting node %d to height=%d\n", node->age, height);
    node->height = height;
}

Node* rotate_right(Node* y) {
    Node* x = y->left;
    // if (!x) return y;
    // printf("asdsadsadsad1\n");
    Node* tmp = x->right;

    // Rot

    x->right = y;
    y->left = tmp;

    // printf("%d\n", x->right->age);
    // printf("%d, %d\n", get_height(x->left), get_height(x->right));
    // printf("%d, %d\n", get_height(y->left), get_height(y->right));

    set_height(y, MAX(get_height(y->left), get_height(y->right)) + 1);
    set_height(x, MAX(get_height(x->left), get_height(x->right)) + 1);

    return x;
}

Node* rotate_left(Node* x) {
    // printf("asdsadsadsad2\n");

    Node* y = x->right;
    // if (!y) return x;
    Node* tmp = y->left;

    // Rot
    y->left = x;
    x->right = tmp;

    set_height(x, MAX(get_height(x->left), get_height(x->right)) + 1);
    set_height(y, MAX(get_height(y->left), get_height(y->right)) + 1);

    return y;
}

Node* create_node(int age, char* name, Node* parent);

void tree_print_node(Node* node);

Node* avl_insert(Node* node, int age, char* name) {
    if (node == NULL) {
        return create_node(age, name, NULL);
    }

    if (node->age > age) {
        node->left = avl_insert(node->left, age, name);
    } else {
        node->right = avl_insert(node->right, age, name);
    }

    // tree_print_node(node);

    // printf("height before: %d\n", node->height);
    // printf("height left=%d\n", get_height(node->left));
    // printf("height right=%d\n", get_height(node->right));

    set_height(node, MAX(get_height(node->left), get_height(node->right)) + 1);
    // printf("node with age=%d and name=%s\n", node->age, node->name);
    // printf("left: ");
    // if (node->left != NULL) {
    //     printf("%d\n", node->left->age);
    // } else {
    //     printf("NULL\n");
    // }

    // printf("right: ");
    // if (node->right != NULL) {
    //     printf("%d\n", node->right->age);
    // } else {
    //     printf("NULL\n");
    // }
    // printf("height after: %d\n", node->height);

    int height_diff = get_height_diff(node);
    // printf("height_diff: %d\n", height_diff);

    if (height_diff > 1 && age < node->left->age) {
        return rotate_right(node);
    }

    if (height_diff < -1 && age > node->right->age) {
        return rotate_left(node);
    }

    if (height_diff > 1 && age > node->left->age) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    if (height_diff < -1 && age < node->right->age) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

Node* find_min_sub_node(Node* node) {
    if (!node->left) return node;
    return find_min_sub_node(node->left);
}

Node* avl_erase(Node* node, int age, char* name) {
    if (node == NULL) return node;

    if (age < node->age) {
        node->left = avl_erase(node->left, age, name);
    } else if (age > node->age) {
        node->right = avl_erase(node->right, age, name);
    }
    // Age is the same as in node
    else if (age == node->age && strcmp(name, node->name) == 0) {
        if (node->left == NULL || node->right == NULL) {
            Node* tmp;
            if (node->left != NULL) {
                tmp = node->left;
                node->left = NULL;
            } else {
                tmp = node->right;
                node->right = NULL;
            }

            if (tmp == NULL) {
                tmp = node;
                node = NULL;
            } else {
                node->name = tmp->name;
                node->age = tmp->age;
            }

            free(tmp);
        } else {
            Node* tmp = find_min_sub_node(node->right);
            // printf("find_min_sub_tree(%i, %s) = (%i, %s)\n", node->age,
            //        node->name, tmp->age, tmp->name);

            node->age = tmp->age;
            node->name = tmp->name;

            node->right = avl_erase(node->right, tmp->age, tmp->name);
        }
    } else {
        return node;
    }

    if (node == NULL) {
        return node;
    }

    node->height = MAX(get_height(node->left), get_height(node->right)) + 1;

    int height_diff = get_height_diff(node);

    if (height_diff > 1 && get_height_diff(node->left) >= 0) {
        return rotate_right(node);
    }

    if (height_diff > 1 && get_height_diff(node->left) < 0) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    if (height_diff < -1 && get_height_diff(node->right) <= 0) {
        return rotate_left(node);
    }

    if (height_diff < -1 && get_height_diff(node->right) > 0) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

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
    // printf("Deleting node with name %s\n", node->name);

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
    node->height = 1;

    return node;
}

void inorder_print(Node* node) {
    if (node != NULL) {
        inorder_print(node->left);
        printf("%i, ", node->age);
        inorder_print(node->right);
    }
}

// Helper function: you are allowed to change this to your preferences
void node_insert(Node* node, int age, char* name) {
    avl_insert(node, age, name);

    return;
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
        tree->root = avl_insert(tree->root, age, name);
        // printf("\ninsert with age %d and name %s: height=%i\n\n", age, name,
        //        tree->root->height);
        // // printf("insert - Root is %p for %i and %s\n", tree->root, age, name);
        // tree->root = node_insert(tree->root, age, name);
    }
}

Node* find_max_sub_node(Node* asd) { return NULL; }

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
    tree->root = avl_erase(tree->root, age, name);
    // printf("erase - Root is %p for %i and %s\n", tree->root, age, name);

    return;
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
