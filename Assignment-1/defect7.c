#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char**argv) {
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

  buf = malloc(len + 1);

  read(fd, buf, len);

  buf[len] = '\0'; // null terminate buf

  // NO FREE

  return 0;
}