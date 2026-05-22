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
int number, numbers_len;


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

    if (strcmp(buffer, "bye") == 0) {
      sendto(sockfd, buffer, sizeof buffer, 0, (struct sockaddr*) &cliaddr, cliaddr_size);
      break;
    }

    FILE *bufstream = fmemopen(buffer, BUFSIZE, "r");
    fscanf(bufstream, "%d", &numbers_len);

    int result = 0;
    for (size_t i = 0; i < numbers_len; ++i) {
      if (fscanf(bufstream, "%d", &number))
        result += number;
    }

    fclose(bufstream);


    sendto(sockfd, &result, sizeof result, 0, (struct sockaddr*) &cliaddr, cliaddr_size);
    printf("[out] %d\n", result);
  }

  close(sockfd);

  return 0;
}
