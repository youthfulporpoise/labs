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


char buffer[BUFSIZE];
int vowelc;


void interrupt(char *msg, int code)
{
  fprintf(stderr, "%s\n", msg);
  exit(code);
}


int main(int argc, char **argv)
{
  if (argc != 2) {
    printf("%s <port number>\n", argv[0]);
    return 0;
  }

  struct sockaddr_in srvaddr;
  srvaddr.sin_family = AF_INET;
  srvaddr.sin_port = htons(atoi(argv[1]));
  srvaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  socklen_t srvaddr_size = sizeof (srvaddr);

  int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0)
    interrupt("[err] create socket failed", 1);

  while (true) {
    printf("Input: ");
    scanf(" %[^\n]", buffer);
    sendto(sockfd, buffer, sizeof buffer, 0, (struct sockaddr*) &srvaddr, srvaddr_size);

    if (strcmp(buffer, "bye") == 0)
      break;

    recvfrom(sockfd, &buffer, strlen(buffer), 0, (struct sockaddr*) &srvaddr, &srvaddr_size);
    recvfrom(sockfd, &vowelc, sizeof vowelc, 0, (struct sockaddr*) &srvaddr, &srvaddr_size);
    printf("\nResult\nString: %s\nVowels: %d\n\n", buffer, vowelc);
  }

  close(sockfd);

  return 0;
}
