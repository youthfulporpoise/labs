#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

/* import list
 *
 * sys/socket.h - socket, bind, listen
 * netinet/in.h - sockaddr_in
 * unistd.h - close
 */


/* rudimentary function to print a message to stderr and exit with the specified exit
 * status */

void interrupt(char *msg, int code)
{
  fprintf(stderr, "%s\n", msg);
  exit(code);
}

/* for return values needed for error checking */
/* for message buffering */

int ret;
char buffer[1024];


int main(int argc, char **argv)
{
  struct sockaddr_in srvaddr;
  srvaddr.sin_family = AF_INET;
  srvaddr.sin_port = htons(8090);
  srvaddr.sin_addr.s_addr = htons(INADDR_ANY);

  int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0)
    interrupt("[err] create socket failed", 1);

  puts("[ok] socket created");

  ret = bind(sockfd, (struct sockaddr*) &srvaddr, sizeof (srvaddr));
  if (ret < 0)
    interrupt("[err] bind socket failed", 1);

  puts("[ok] socket bound at port 8090");

  struct sockaddr_in cliaddr;
  socklen_t cliaddr_size = sizeof (cliaddr);

  while (true) {
    recvfrom(sockfd, buffer, sizeof (buffer), 0, (struct sockaddr*) &cliaddr, &cliaddr_size);
    printf("[incoming] %s\n", buffer);

    sendto(sockfd, buffer, sizeof (buffer), 0, (struct sockaddr*) &cliaddr, cliaddr_size);
    printf("[outgoing] %s\n", buffer);

    if (strcmp(buffer, "bye") == 0)
      break;
  }

  close(sockfd);

  return 0;
}
