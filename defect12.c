

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define MAX_SIZE 256

int isValid(char * url) {
    return 1;
}


int main(int argc, char ** argv) {
    char buff1[MAX_SIZE], buff2[MAX_SIZE];
    // make sure url a valid URL and fits in buff1 and buff2:
    
    char * url = "www.google.com/hello/fran";
    // char * url = "www.google.com";


    if (!isValid(url)) {
        return 1;
    }
    
    if (strlen(url) > MAX_SIZE - 1) {
        return 1;
    }
    
    // copy url up to first separator, ie. first ’/’, to buff1
    char * out = buff1;
    
    do {
     // skip spaces
        if (*url != ' ') {
            *out = *url;
            out++;
        }
    // ISSUE: If the url does not contain '/' we will read until the end
    // of the world :(.
    } while (*url++ != '/');
    

    // ISSUE: buff1 will not contain the \0 meaning we read/write garbage
    strcpy(buff2, buff1);

    return 0;
}