#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>

#define     BUFSIZE       1024
#define     DFALIM        256


char buffer[BUFSIZE];

struct dfa {
  size_t statec;

  char ipsym[DFALIM];
  size_t ipsymc;

  size_t acc[DFALIM];
  size_t accn;

  size_t delta[DFALIM][DFALIM];
};


void sigint_handler(int signum)
{
  puts("\nExiting...");
  exit(0);
}


ssize_t validate_ipsym(struct dfa dfa, char c)
{
  for (size_t i = 0; i < dfa.ipsymc; ++i)
    if (dfa.ipsym[i] == c)
      return (ssize_t) i;
  return -1;
}


bool is_accepting_state(struct dfa dfa, size_t state)
{
  for (size_t i = 0; i < dfa.accn; ++i) {
    if (dfa.acc[i] == state)
      return true;
  }
  return false;
}


void execute_dfa(struct dfa dfa)
{
  size_t state = 0;

  printf("String: ");
  scanf(" %s", buffer);

  ssize_t idx;
  char *c = buffer;
  while (*c != '\0') {
    idx = validate_ipsym(dfa, *c);

    if (idx < 0) {
      printf("%c is not a valid input symbol.\n", *c);
      return;
    } else state = dfa.delta[state][idx];

    c++;
  }

  printf(
    "%s %s accepted.\n", 
    buffer,
    is_accepting_state(dfa, state) ? "is" : "is not"
  );
}


int main(int argc, char **argv)
{
  signal(SIGINT, sigint_handler);

  struct dfa dfa;

  /* Number of States */
  printf("|Q| = ");
  scanf(" %zu", &dfa.statec);

  /* Input Symbols */
  printf("Σ : ");
  scanf(" %[^\n]", buffer);

  dfa.ipsymc = 0;
  for (size_t i = 0; buffer[i] != '\0'; ++i) {
    if (buffer[i] == ' ');
    else
      dfa.ipsym[dfa.ipsymc++] = buffer[i];
  }

  /* Accepting States */
  printf("|A| = ");
  scanf(" %zu", &dfa.accn);

  printf("A : ");
  for (size_t i = 0; i < dfa.accn; ++i)
    scanf(" %zu", &dfa.acc[i]);

  /* Transition Function */
  printf("\n");
  for (size_t i = 0; i < dfa.statec; ++i) {
    for (size_t j = 0; j < dfa.ipsymc; ++j) {
      printf("δ(q%zu, %c) = ", i, dfa.ipsym[j]);
      scanf(" %zu", &dfa.delta[i][j]);
    }
  }

  while (true) {
    printf("\n");
    execute_dfa(dfa);
  }
}
