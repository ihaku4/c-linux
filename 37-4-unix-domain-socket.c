#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <sys/socket.h>
#include <sys/un.h>

int main(void)
{
  int fd, size;
  struct sockaddr_un un;

  memset(&un, 0, sizeof(un));
  un.sun_family = AF_UNIX;
  strcpy(un.sun_path, "foo.socket");
  if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
    perror("socket error");
    exit(1);
  }
  size = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);
  if (bind(fd, (struct sockaddr *)&un, size) < 0) {
    perror("bind error");
    exit(1);
  }
  printf("UNIX domain socket bound\n");
  exit(0);
}
