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

#define       BUFSIZE       1024

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
char buffer[BUFSIZE];


int main(int argc, char **argv)
{
  if (argc != 2) {
    printf("%s <port number>\n", argv[0]);
    return 0;
  }

  struct sockaddr_in srvaddr;
  srvaddr.sin_family = AF_INET;
  srvaddr.sin_port = htons(atoi(argv[1]));
  srvaddr.sin_addr.s_addr = htons(INADDR_ANY);

  int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0)
    interrupt("[err] create socket failed", 1);

  puts("[ok] socket created");

  ret = bind(sockfd, (struct sockaddr*) &srvaddr, sizeof (srvaddr));
  if (ret < 0)
    interrupt("[err] bind socket failed", 1);

  printf("[ok] socket bound at port %s\n", argv[1]);

  struct sockaddr_in cliaddr;
  socklen_t cliaddr_size = sizeof (cliaddr);

  while (true) {
    recvfrom(sockfd, buffer, sizeof buffer, 0, (struct sockaddr*) &cliaddr, &cliaddr_size);
    printf("[in] %s\n", buffer);

    /* check whether the input is 'bye' */

    if (strcmp(buffer, "bye") == 0) {
      sendto(sockfd, buffer, sizeof buffer, 0, (struct sockaddr*) &cliaddr, cliaddr_size);
      break;
    }

    /* convert to uppercase and count the number of vowels */

    int vowelc = 0;
    char c;
    for (size_t i = 0; i < strlen(buffer); ++i) {
      c = buffer[i];

      if ('a' <= c && c <= 'z')
        buffer[i] -= 0x20;

      if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        vowelc++;
    }

    sendto(sockfd, &buffer, sizeof buffer, 0, (struct sockaddr*) &cliaddr, cliaddr_size);
    sendto(sockfd, &vowelc, sizeof vowelc, 0, (struct sockaddr*) &cliaddr, cliaddr_size);
    printf("[out] %s\n", buffer);
  }

  close(sockfd);

  return 0;
}
