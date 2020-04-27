#include <stdio.h>
#include <stdlib.h>

#define SIZE 1337

int main(int argc, char* argv[]) {
  char* ptr = (char*)malloc (SIZE);
  
  int abrt = argc & 1;

  if (abrt) {
    free(ptr);
  }
  
  // ISSUE: If abrt == true we do a double free
  free(ptr);
}


