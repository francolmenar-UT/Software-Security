#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>


int main (int argc, char ** argv) {

  int fd;

  if (argc != 2) {
    fd = open("readfile.in", O_RDONLY);
  } else {
    fd = open(argv[1], O_RDONLY);
  }

  char *buf;
  int i, len;
  read(fd, &len, sizeof(len));

  if (len < 0) {
    error ("negative length");
    return 1;
  }

  buf = malloc(len);
  read(fd, buf, len);

  // Missing free

  return 0;
}