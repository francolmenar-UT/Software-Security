#include <string.h>

int main(int argc, char ** argv) {
    char src[9];
    char dest[9];
    char* base_url = "www.ru.nl";
    strncpy(src, base_url, 9);
    // copies base_url to src
    strcpy(dest, src);
    // copies src to dest
}