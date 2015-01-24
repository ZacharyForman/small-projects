#include <fcntl.h>
#include <stdio.h>

#define LEN 1024

int main(int argc, char *argv[])
{

  if (argc < 3) {
    printf("Usage: %s f1 f2\n", argv[0]);
    return 1;
  }

  int fd1, fd2;
  fd1 = open(argv[1], O_RDONLY);
  fd2 = open(argv[2], O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);

  int len;
  char buf[LEN];
  while ((len = read(fd1, buf, LEN)) > 0)
    write(fd2, buf, len);

  close(fd1);
  close(fd2);
}