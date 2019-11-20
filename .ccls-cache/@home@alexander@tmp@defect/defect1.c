#include  < stdio.h>
#include  < stdlib.h>

  void secret() {
    system("cat /etc/passwd");
    return;
}
void readStdin() {
    char buf[18];
    gets(buf);
    return;
}
int main(int argc, char ** argv) {
    readStdin();
    printf("Nothing happened\n");
    return 0;
}
