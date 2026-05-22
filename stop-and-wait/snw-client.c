#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int seq = 0;
int ack;

void interrupt(char *msg, int code)
{
  fprintf(stderr, "%s\n", msg);
  exit(code);
}


int main(int argc, char **argv)
{
  if (argc != 4) {
    printf("Usage: %s <ipaddr> <port> <frames>", argv[0]);
    return 0;
  }

  struct sockaddr_in srvaddr;
  srvaddr.sin_family = AF_INET;
  srvaddr.sin_port = htons(atoi(argv[2]));
  srvaddr.sin_addr.s_addr = inet_addr(argv[1]);

  socklen_t srvaddr_size = sizeof srvaddr;

  int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0)
    interrupt("[err] create socket failed", 1);

  int frmno = atoi(argv[3]);
  sendto(sockfd, &frmno, sizeof frmno, 0, (struct sockaddr*) &srvaddr, srvaddr_size);

  int sent = 0;
  while (sent < frmno) {
    sendto(sockfd, &seq, sizeof seq, 0, (struct sockaddr*) &srvaddr, srvaddr_size);
    printf("[sent] seq = %d\n", seq);

    recvfrom(sockfd, &ack, sizeof ack, 0, (struct sockaddr*) &srvaddr, &srvaddr_size);
    if (ack == -1) {
      printf("[rcvd] nak; resending...\n");
      continue;
    } else {
      printf("[rcvd] ack\n");
      if (ack == 1 - seq) {
        seq = ack;
        sent++;
      } else printf("[err] unexpected ack; resending...\n");
    }
  }

  printf("Okay. %d frame(s) sent.\n", frmno);
  close(sockfd);
  return 0;
}
