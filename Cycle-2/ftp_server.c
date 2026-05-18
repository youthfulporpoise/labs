#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define     BUFSIZE     4096


int ret;
char buffer[BUFSIZE];
char filename[BUFSIZE];
char cmd[16];


void interrupt(char *msg, int code)
{
  fprintf(stderr, "%s\n", msg);
  exit(code);
}


int main(int argc, char **argv)
{
  if (argc != 2) {
    printf("Usage: %s <port number>\n", argv[0]);
    return 0;
  }

  struct sockaddr_in srvaddr;
  srvaddr.sin_family = AF_INET;
  srvaddr.sin_port = htons(atoi(argv[1]));
  srvaddr.sin_addr.s_addr = INADDR_ANY;

  int sockfd = socket(PF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    interrupt("[err] create socket failed", 1);

  puts("[ok] socket created");

  ret = bind(sockfd, (struct sockaddr*) &srvaddr, sizeof srvaddr);
  if (ret < 0)
    interrupt("[err] establish connection failed", 1);

  puts("[ok] socket bound at port 8090");

  ret = listen(sockfd, 5);
  if (ret < 0)
    interrupt("[err] listen to socket failed", 1);

  puts("[ok] listening to socket");

  struct sockaddr_in cliaddr;
  socklen_t cliaddr_size = sizeof cliaddr;

  int clifd = accept(sockfd, (struct sockaddr*) &cliaddr, &cliaddr_size);
  if (clifd < 0)
    interrupt("[err] could not accept client connection", 1);

  puts("[ok] connection accepted");

  while (true) {
    recv(clifd, cmd, sizeof cmd - 1, 0);
    if (!strcmp(cmd, "PUT")) {
      recv(clifd, filename, sizeof filename - 1, 0);
      printf("\nPUT: %s\n", filename);
      int count = recv(clifd, buffer, sizeof buffer, 0);

      FILE *file = fopen(filename, "w");
      fwrite(buffer, sizeof (char), count, file);
      fclose(file);

    } else if (!strcmp(cmd, "GET")) {
      recv(clifd, filename, sizeof filename - 1, 0);
      printf("\nGET: %s\n", filename);

      FILE *file = fopen(filename, "r");
      int count = fread(buffer, sizeof (char), sizeof buffer - 1, file);
      fclose(file);

      send(clifd, buffer, count, 0);

    } else if (!strcmp(cmd, "QUIT")) {
      puts("\nQuitting...");
      break;
    }
  }

  close(sockfd);
  return 0;
}
