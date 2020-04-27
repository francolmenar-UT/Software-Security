#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define MAX_BUF 256
void BadCode (char* input) {
    short len;

    char buf[MAX_BUF];
    // ISSUE: If the length of the input is longer than
    // 32,767 (max positive number of 16-bit, assuming short is 16-bit),
    // it will be represented in 16-bits. This means we start copying the
    // string until we find \0, but can write more than 256 chars.
    len = strlen(input);

    if (len < MAX_BUF) {
        strcpy(buf, input);
    }
}

int main(int argc, char ** argv) {

    char * my_input = "hello fran!";

    BadCode(my_input);

    return 0;
}