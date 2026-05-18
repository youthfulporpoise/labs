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
  srvaddr.sin_port = htons(8090);
  srvaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  socklen_t srvaddr_size = sizeof (srvaddr);

  int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0)
    interrupt("[err] create socket failed", 1);

  while (true) {
    printf("[outgoing]> ");
    scanf(" %[^\n]", buffer);
    sendto(sockfd, buffer, sizeof (buffer), 0, (struct sockaddr*) &srvaddr, srvaddr_size);

    bzero(buffer, BUFSIZE);
    recvfrom(sockfd, buffer, sizeof (buffer), 0, (struct sockaddr*) &srvaddr, &srvaddr_size);
    printf("[incoming] %s\n", buffer);

    if (strcmp(buffer, "bye") == 0)
      break;
  }

  close(sockfd);

  return 0;
}
