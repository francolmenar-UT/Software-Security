#include <stdio.h>
int main(int argc, char* argv[]) {
    if (argc > 1)
        // ISSUE: Use string formatting
        printf(argv[1]);
        // printf("the value somewhere in the program is: %i\n");

    return 0;
}
