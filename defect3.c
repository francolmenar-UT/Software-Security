#include <string.h>
#include <stdio.h>


void valid() {
    char buf[20];
    char prefix[] = "http://";
    char *path = "hej.com";
    strcpy(buf, prefix);
    // copies the string prefix to buf
    strncat(buf, path, sizeof(buf));
    // concatenates path to the string buf
    printf("valid: %s\n", buf);
}

void invalid() {
    char buf[20];
    char prefix[] = "http://";
    // To long for buf[20]
    char *path = "0123456789ABCDEFGHIJKLMNO.com";
    strcpy(buf, prefix);
    // copies the string prefix to buf. Will now copy n+1
    strncat(buf, path, sizeof(buf));
    // concatenates path to the string buf
    printf("invalid: %s\n", buf);

}


int main () {
    valid();
    invalid();
}

// char buf[20];
// char prefix[] = "http://";
// ...
// strcpy(buf, prefix);
// // copies the string prefix to buf
// strncat(buf, path, sizeof(buf));
// // concatenates path to the string buf
