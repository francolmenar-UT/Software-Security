#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv) {  
    char dest[20];
    // Added to test different strings easily
    if (argc != 2) {
        printf("Expected one argument with src string\n");
        exit(EXIT_FAILURE);
    }

    // ADDED
    // This one will not complain with cppcheck because it doesn't know that src
    // can be longer than dest
    // char *src = argv[1];

    // This one will complain with cppcheck because it is known at compile
    // time that the src buffer size > dest buffer size
    char src[30] = "123456789012345678901234";

    // UNSAFE: If length of src is longer than length of dest, we write past
    // the allocated memory of dest.
    strcpy(dest, src); // copies string src to dest

    printf("%s\n", dest);

    return 0;
}
