#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char ** argv) {
  int fd;

  if (argc != 2) {
    fd = open("readfile.in", O_RDONLY);
  } else {
    fd = open(argv[1], O_RDONLY);
  }

  char *buf;
  int i, len;
  
  // The int read can be a negative number...
  ssize_t read_bytes = read(fd, &len, sizeof(int));
  
  printf("Length: %i\n", len);
  printf("Read bytes: %li\n", read_bytes);
  
  // read sizeof(int) bytes, ie. an int,
  // and store these at &len, ie. the
  // memory address of the variable len

  // In this file there is not really an issue if the len that is read is
  // negative, as both malloc and read uses unsigned for their length paramters.
  // This means in the case of a negative number we will just allocate and read
  // a lot of data. Of course trying to allocate too much might fail...

  buf = malloc(len);
  read(fd,buf,len); // read len bytes into buf


  // Missing free for buf

  return 0;
}