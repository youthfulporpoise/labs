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


/* key-value data in the server */
#define         DATALEN         9

char *data[DATALEN][2] = {
  { "prime-minister",     "Narendra Modi" },
  { "defence",            "Rajnath Singh" },
  { "home-affairs",       "Amit Shah" },
  { "transport",          "Nitin Gadkari" },
  { "finance",            "Nirmala Sitharaman" },
  { "commerce",           "Piyush Goyal" },
  { "education",          "Dharmendra Pradhan" },
  { "tourism",            "Gajendra Singh Shekhawat" },
  { "food",               "Chirag Paswan" }
};

char *lookup(char *key)
{
    for (size_t i = 0; i < DATALEN; ++i)
        if (strcmp(data[i][0], key) == 0)
            return data[i][1];
    return NULL;
}


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

  int sockfd = socket(PF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    interrupt("[err] create socket failed", 1);

  puts("[ok] socket created");

  ret = bind(sockfd, (struct sockaddr*) &srvaddr, sizeof (srvaddr));
  if (ret < 0)
    interrupt("[err] bind socket failed", 1);

  puts("[ok] socket bound at port 8090");

  ret = listen(sockfd, 5);
  if (ret < 0)
    interrupt("[err] listen to socket failed", 1);

  puts("[ok] listening to socket");

  struct sockaddr_in cliaddr;
  socklen_t cliaddr_size = sizeof (cliaddr);

  int clifd = accept(sockfd, (struct sockaddr*) &cliaddr, &cliaddr_size);
  if (clifd < 0)
    interrupt("[err] accept connection failed", 1);

  puts("[ok] connection accepted");

  char *result;
  while (true) {
    recv(clifd, buffer, sizeof (buffer), 0);
    printf("[incoming] %s\n", buffer);

    result = lookup(buffer);

    if (strcmp(buffer, "bye") == 0);
    else if (result == NULL)
      strcpy(buffer, "not found");
    else
      strcpy(buffer, result);

    send(clifd, buffer, strlen(buffer), 0);
    printf("[outgoing] %s\n", buffer);

  }

  close(clifd);
  close(sockfd);

  return 0;
}
