#include <stdio.h>
#include <stdlib.h>

void secret() {
    system("cat /etc/passwd");
    return;
}

void readStdin() {
    char buf[18];
    // If the user inputs a string which is more than 18 characters
    // (null-termination included), this will write user data to the stack.
    // This can be exploited to write the address of secret() to the stack,
    // which will give the user access to un-authorized code.
    gets(buf);
    return;
}

int main(int argc, char ** argv) {
    readStdin();
    printf("Noting happened\n");
    return 0;
}