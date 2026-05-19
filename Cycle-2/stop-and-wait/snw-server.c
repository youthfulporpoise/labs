#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


int ack = 0;
int nak = -1;
int seq = 0;

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
    interrupt("[err] establish connection failed", 1);

  puts("[ok] listening to socket");

  struct sockaddr_in cliaddr;
  socklen_t cliaddr_size = sizeof cliaddr;

  int frmno;
  recvfrom(sockfd, &frmno, sizeof frmno, 0, (struct sockaddr*) &cliaddr, &cliaddr_size);

  int sent = 0;
  while (sent < frmno) {
    recvfrom(sockfd, &seq, sizeof seq, 0, (struct sockaddr*) &cliaddr, &cliaddr_size);
    if (rand() % 4 == 0) {
      sendto(sockfd, &nak, sizeof nak, 0, (struct sockaddr*) &cliaddr, cliaddr_size);
      printf("[nak] timeout: NAK");
    } else if (seq == ack) {
      ack = 1 - seq;
      sendto(sockfd, &ack, sizeof ack, 0, (struct sockaddr*) &cliaddr, cliaddr_size);
      printf("[ack] correct frame: ACK %d\n", seq);
      sent++;
    } else {
      sendto(sockfd, &nak, sizeof nak, 0, (struct sockaddr*) &cliaddr, cliaddr_size);
      printf("[nak] incorrect: NAK");
    }
  }

  close(sockfd);
  return 0;
}

/* The client sends a frame of data and waits until timeout for the acknowledgement from
 * the server. The server on the other side, for each data frame received, will send
 * back a corresponding acknowledgement frame. This goes back and forth.
 *
 * +-------+       +-------+
 * |   A   |       |   B   |
 * +-------+       +-------+
 *     |    DATA0      |
 *     |  --------->   |
 *     |    ACK0       |
 *     |  <---------   |
 *     |    DATA1      |    
 *     |  --------->   |
 *     |    ACK1       |
 */
