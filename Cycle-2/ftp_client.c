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
char filename[BUFSIZE];
char cmd[16];


void interrupt(char *msg, int code)
{
  fprintf(stderr, "%s\n", msg);
  exit(code);
}


int main(int argc, char **argv)
{
  if (argc != 2) {
    printf("Usage: %s <ip address> <port number>\n", argv[0]);
    return 0;
  }

  struct sockaddr_in srvaddr;
  srvaddr.sin_family = AF_INET;
  srvaddr.sin_port = htons(atoi(argv[2]));
  srvaddr.sin_addr.s_addr = inet_addr(argv[1]);

  socklen_t srvaddr_size = sizeof (srvaddr);

  int sockfd = socket(PF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    interrupt("[err] create socket failed", 1);

  ret = connect(sockfd, (struct sockaddr*) &srvaddr, sizeof srvaddr);
  if (ret < 0)
    interrupt("[err] establish connection failed", 1);

  while (true) {
    printf("> ");
    scanf("%s %[^\n]", cmd, filename);

    if (strcmp(cmd, "bye") == 0) {
      strcpy(buffer, "CLOSE_CXN");
      sendto(sockfd, buffer, sizeof buffer, 0, (struct sockaddr*) &srvaddr, srvaddr_size);
      break;

    } else if (strcmp(cmd, "put") == 0) {
      /* put file */

      strcpy(buffer, "FILE_READY");
      sendto(sockfd, buffer, sizeof buffer, 0, (struct sockaddr*) &srvaddr, srvaddr_size);

      FILE *file = fopen(filename, "r");
      int c;
      while ((c = fgetc(file)) != EOF)
        sendto(sockfd, &c, sizeof c, 0, (struct sockaddr*) &srvaddr, srvaddr_size);
      fclose(file);

    } else if (strcmp(cmd, "get") == 0) {
      /* get file */
      
      sprintf(buffer, "GET %s", filename);
      sendto(sockfd, buffer, sizeof buffer, 0, (struct sockaddr*) &srvaddr, srvaddr_size);

      recvfrom(sockfd, buffer, sizeof buffer, 0, (struct sockaddr*) &srvaddr, &srvaddr_size);
      if (strcmp(buffer, "FILE_READY") != 0)
        break;

      FILE *file = fopen(filename, "a");
      int c;
      while (c != EOF) {
        recvfrom(sockfd, &c, sizeof c, 0, (struct sockaddr*) &srvaddr, &srvaddr_size);
        fputc(c, file);
      }
      fclose(file);

    } else {
      printf("%s: invalid cmd\n", cmd);
      break;
    }

    /* transaction end status */

    recvfrom(sockfd, buffer, sizeof buffer, 0, (struct sockaddr*) &srvaddr, &srvaddr_size);
    printf("[in] %s\n", buffer);
  }

  close(sockfd);

  return 0;
}
