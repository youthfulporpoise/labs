#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define       ARRSZ       256
#define       BUFSZ       2048
#define       STKSZ       512


struct op_val {
  char c;
  ssize_t v;
} ipsym[ARRSZ];
size_t ipsym_n;

struct production {
  char c;
  char p[32][32];
  size_t n_p;
} grmr[ARRSZ];
size_t grmr_n;

char buffer[BUFSZ];

char stack[STKSZ];
size_t t = 0;


/* Return whether terminal or not.
 */
bool is_terminal(char c)
{
  for (size_t i = 0; i < ipsym_n; ++i)
    if (c == ipsym[i].c)
      return true;
  return false;
}

/* Return whether nonterminal or not
 */
bool is_nonterminal(char c)
{
  for (size_t i = 0; i < grmr_n; ++i)
    if (c == grmr[i].c)
      return true;
  return false;
}


/* Returns precedence of each character
 */
ssize_t prec(char c)
{
  for (size_t i = 0; i < ipsym_n; i++)
    if (ipsym[i].c == c)
      return ipsym[i].v;
  return SSIZE_MAX;
}

/* Parses each part of a production
   E -> E+E|E*E will be parsed into E+E and E*E. 
 */
void parse_prod(size_t idx)
{
  char delim[] = "|";
  char *tok = strtok(buffer, delim);
  size_t n = 0;

  while (tok != NULL) {
    printf("Token: %s\n", tok);
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

char get_top_terminal(void)
{
  size_t i = t;
  while (i > 0) {
    if (is_terminal(stack[i - 1]))
      return stack[i - 1];
    --i;
  }
  return '$';
}

/* The main parsing procedure
 */
void op_parse(char *input)
{
  size_t input_strlen = strlen(input);
  input[input_strlen] = '$';
  input[++input_strlen] = '\0';
  stack[t++] = '$';
  stack[t] = '\0';

  char a, b;

  size_t i = 0;
  while (input[i] != '$' || strlen(stack) > 2) {
    /* Just in case if t happens go below 1
     */ 
    if (t < 1)
      break;

    a = get_top_terminal();
    b = input[i];

    stack[t] = '\0';
    printf("(%c) [ %-16s ] [ %16s ] (%c) <%zu>\n", a, stack, input + i, b, t);

    if (prec(a) <= prec(b)) {
      if (b != '$') {
        stack[t++] = b;
        i++;
      }
    } else if (prec(a) > prec(b)) {
      stack[t] = '\0';
      do {
        if (t > 0) t--;
        else break;
        a = stack[t - 1];
        if (reduce_handle(stack + t)) break;
        else if (t <= 1) break;
      } while (prec(a) > prec(b));
    } 
  }

  printf("(%c) [ %-16s ] [ %16s ] (%c)\n", a, stack, input + i, b);

  sprintf(buffer, "$%c", grmr[0].c);
  if (strcmp(buffer, stack) == 0)
    printf("Accepted.\n");
  else
    printf("Rejected.\n");

  t = 0;
}

int main(int argc, char **argv)
{
  printf("Number of terminal symbols: ");
  scanf(" %zu", &ipsym_n);
  ipsym_n += 1;

  printf("<Symbol> <Precedence>:\n");
  printf("$ 0\n");
  ipsym[0].c = '$';
  ipsym[0].v = -1;

  for (size_t i = 1; i < ipsym_n; ++i)
    scanf(" %c %zu", &ipsym[i].c, &ipsym[i].v);

  printf("\nNumber of nonterminal symbols: ");
  scanf(" %zu", &grmr_n);

  printf("<Symbol> -> <Productions>:\n");
  for (size_t i = 0; i < grmr_n; ++i) {
    scanf(" %c -> %s", &grmr[i].c, buffer);
    parse_prod(i);
  }

  char input[BUFSZ];
  while (true) {
    printf("\nInput: ");
    scanf(" %s", input);
    op_parse(input);
  }
}
