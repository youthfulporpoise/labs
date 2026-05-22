#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int seq = 0;
int ack = 0;
int nak = 0;

int ret;


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

  int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0)
    interrupt("[err] create socket failed", 1);
  puts("[ok] socket created");

  ret = bind(sockfd, (struct sockaddr*) &srvaddr, sizeof srvaddr);
  if (ret < 0)
    interrupt("[err] bind socket failed", 1);
  puts("[ok] listening to socket");

  struct sockaddr_in cliaddr;
  socklen_t cliaddr_size = sizeof cliaddr;

  int frmno;
  recvfrom(sockfd, &frmno, sizeof frmno, 0, (struct sockaddr*) &cliaddr, &cliaddr_size);

  int rcvd = 0;
  while (rcvd < frmno) {
    recvfrom(sockfd, &seq, sizeof seq, 0, (struct sockaddr*) &cliaddr, &cliaddr_size);
    if (rand() % 5 == 0) {
      nak = -ack;
      sendto(sockfd, &nak, sizeof nak, 0, (struct sockaddr*) &cliaddr, cliaddr_size);
      printf("[nak] corrupted: %d\n", nak);
    } else if (seq == ack) {
      sendto(sockfd, &ack, sizeof ack, 0, (struct sockaddr*) &cliaddr, cliaddr_size);
      printf("[ack] correct: %d\n", ack);
      ack++;
      rcvd++;
    } else {
      nak = -ack;
      sendto(sockfd, &nak, sizeof nak, 0, (struct sockaddr*) &cliaddr, cliaddr_size);
      printf("[nak] unknown error: %d\n", nak);
    }
  }
  printf("%d frame(s) received.\n", frmno);

  close(sockfd);
  return 0;
}
