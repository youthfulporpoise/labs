#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define       WINSIZE         (8)
#define       MIN(a, b)       ((a) < (b) ? (a) : (b))


int queue[WINSIZE];
enum {FULL, EMPTY, NEUTRAL} questat = EMPTY;
size_t f = 0;
size_t r = 0;

void enqueue(int v)
{
  queue[r] = v;
  r++;
  if (r == f)
    questat = FULL;
  else
    questat = NEUTRAL;
}

int dequeue(void)
{
  int v = queue[f];
  f++;
  if (f == r)
    questat = EMPTY;
  else
    questat = NEUTRAL;
  return v;
}

int peek()
{
  return queue[f];
}

void stash(void)
{
  f = 0;
  r = 0;
  questat = EMPTY;
}


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
    printf("Usage: %s <ipaddr> <port> <frames>\n", argv[0]);
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
  puts("[ok] socket created");

  int frmno = atoi(argv[3]);
  sendto(sockfd, &frmno, sizeof frmno, 0, (struct sockaddr*) &srvaddr, srvaddr_size);

  int sent = 0;
  while (sent < frmno) {
    if (questat != FULL) {
      sendto(sockfd, &seq, sizeof seq, 0, (struct sockaddr*) &srvaddr, srvaddr_size);
      enqueue(seq);

      printf("[sent] seq = %d\n", seq);
      seq++;
    }

    recvfrom(sockfd, &ack, sizeof ack, 0, (struct sockaddr*) &srvaddr, &srvaddr_size);
    if (ack < 0) {
      printf("[rcvd] corrupt: %d; going back to %d...\n", -ack, -ack);
      seq = -ack;
      stash();
      continue;
    } else {
      printf("[rcvd] correct: %d\n", ack);
      if (peek() == ack) {
        dequeue();
        sent++;
      } else printf("[err] incorrect ack\n");
    }
  }

  close(sockfd);
  return 0;
}
