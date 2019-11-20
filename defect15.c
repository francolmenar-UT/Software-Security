#include <stdio.h>
#include <stdlib.h>

#define SIZE 1337

void logError(char * msg, char * ptr) {
  return;
}

int main(int argc, char* argv[]) {
  char* ptr = (char*)malloc (SIZE);
  
  int err = argc & 1;

  int abrt = 0;

  if (err) {
    abrt = 1;
    free(ptr);
  }
  
  if (abrt) {
    // ISSUE: ptr used after free
    logError("operation aborted before commit", ptr);
  } else {
    // ISSUE: ptr is not free'd
  }

}




