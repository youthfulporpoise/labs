#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <signal.h>

#define       ARRSZ       256
#define       BUFSZ       2048
#define       STKSZ       512


struct production {
  char c;
  char p[32][32];
  size_t n_p;
} grmr[ARRSZ];
size_t grmr_n;

char buffer[BUFSZ];

char stack[STKSZ];
size_t t = 0;


/* Parses each part of a production
   E -> E+E|E*E will be parsed into E+E and E*E. 
 */
void parse_prod(size_t idx)
{
  char delim[] = "|";
  char *tok = strtok(buffer, delim);
  size_t n = 0;

  while (tok != NULL) {
    printf("Production: %s\n", tok);
    strcpy(grmr[idx].p[n], tok);
    n++;
    tok = strtok(NULL, delim);
  }

  grmr[idx].n_p = n;
}

/* Reduce handle of redstk and push into stack
 */
bool reduce_handle(char *stkpart)
{
  strcpy(buffer, stkpart);

  bool found = false;
  for (size_t i = 0; i < grmr_n; i++) {
    for (size_t j = 0; j < grmr[i].n_p; ++j) {
      if (strcmp(stkpart, grmr[i].p[j]) == 0) {
        stack[t++] = grmr[i].c;
        stack[t] = '\0';
        found = true;
        printf("Reduced: %s => %c\n", buffer, grmr[i].c);
      }
    }
  }
  return found;
}

/* The main parsing procedure
 */
void sr_parse(char *input)
{
  size_t input_strlen = strlen(input);
  input[input_strlen] = '$';
  input[++input_strlen] = '\0';
  stack[t++] = '$';
  stack[t] = '\0';

  size_t i = 0;
  while (input[i] != '$' || strlen(stack) > 2) {
    if (t < 1)
      break;

    stack[t] = '\0';
    printf(
      "(%c) [ %-16s ] [ %16s ] (%c)\n",
      stack[t - 1],
      stack,
      input + i,
      input[i]
    );

    size_t t_bk = t;

    do {
      if (t > 0) t--;
      else break;
      if (reduce_handle(stack + t)) {
        t_bk = t;
      } else if (t < 1) {
        if (input[i] == '$') goto check_accepted;
        else {
          break;
          t = t_bk;
        }
      }
    } while (t > 0);

    t = t_bk;

    if (input[i] != '$') {
      stack[t++] = input[i];
      i++;
    }
  }

  check_accepted:
    sprintf(buffer, "$%c", grmr[0].c);
    if (strcmp(buffer, stack) == 0)
      printf("Accepted.\n");
    else
      printf("Rejected.\n");

  t = 0;
}

/* Catch the interrupt signal and handle
 */
void handle_sigint(int sig)
{
  printf("\nExiting...\n");
  exit(sig);
}


int main(int argc, char **argv)
{
  signal(SIGINT, handle_sigint);

  printf("No. of grammar nonterminal symbols: ");
  scanf(" %zu", &grmr_n);

  for (size_t i = 0; i < grmr_n; ++i) {
    scanf(" %c -> %s", &grmr[i].c, buffer);
    parse_prod(i);
  }

  char input[BUFSZ];
  while (true) {
    printf("\nInput: ");
    scanf(" %s", input);
    sr_parse(input);
  }
}
