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
  if (argc != 3) {
    printf("Usage: %s <ip address> <port number>\n", argv[0]);
    return 0;
  }

  struct sockaddr_in srvaddr;
  srvaddr.sin_family = AF_INET;
  srvaddr.sin_port = htons(atoi(argv[2]));
  srvaddr.sin_addr.s_addr = inet_addr(argv[1]);

  socklen_t srvaddr_size = sizeof (srvaddr);

  int sockfd = socket(PF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    interrupt("[err] create socket failed", 1);

  ret = connect(sockfd, (struct sockaddr*) &srvaddr, sizeof srvaddr);
  if (ret < 0)
    interrupt("[err] establish connection failed", 1);

  while (true) {
    printf("ftp> ");
    scanf(" %s", cmd);

    send(sockfd, cmd, strlen(cmd) + 1, 0);
    if (!strcmp(cmd, "PUT")) {
      scanf(" %[^\n]", filename);
      send(sockfd, filename, strlen(filename) + 1, 0);

      FILE *file = fopen(filename, "r");
      int count = fread(buffer, sizeof (char), sizeof buffer - 1, file);
      fclose(file);

      send(sockfd, buffer, count, 0);

    } else if (!strcmp(cmd, "GET")) {
      scanf(" %[^\n]", filename);
      send(sockfd, filename, strlen(filename) + 1, 0);
      int count = recv(sockfd, buffer, sizeof buffer - 1, 0);

      FILE *file = fopen(filename, "w");
      fwrite(buffer, sizeof (char), count, file);
      fclose(file);

    } else if (!strcmp(cmd, "QUIT")) {
      puts("Exiting...");
      break;
    }
  }

  close(sockfd);
  return 0;
}
