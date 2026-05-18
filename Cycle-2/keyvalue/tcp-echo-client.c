#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

/* import list
 *
 * arpa/inet.h - inet_addr
 */

#define     BUFSIZE     1024


int ret;
char buffer[BUFSIZE];


void interrupt(char *msg, int code)
{
  fprintf(stderr, "%s\n", msg);
  exit(code);
}


int main(int argc, char **argv)
{
  struct sockaddr_in srvaddr;
  srvaddr.sin_family = AF_INET;
  srvaddr.sin_port = htons(8091);
  srvaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  int sockfd = socket(PF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    interrupt("[err] create socket failed", 1);

  ret = connect(sockfd, (struct sockaddr*) &srvaddr, sizeof (srvaddr));
  if (ret < 0)
    interrupt("[err] connection failed", 1);

  while (true) {
    printf("[outgoing]> ");
    scanf(" %[^\n]", buffer);
    send(sockfd, buffer, sizeof (buffer), 0);

    bzero(buffer, BUFSIZE);
    recv(sockfd, buffer, sizeof (buffer), 0);
    printf("[incoming] %s\n", buffer);

    if (strcmp(buffer, "bye") == 0)
      break;
  }

  close(sockfd);

  return 0;
}
