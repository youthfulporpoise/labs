#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define         STKSZ         4096


char stack[STKSZ];
size_t t = 0;

void call_error(size_t line_no, char c1, char c2)
{
  if (c1 == '\0')
    printf("%zu: unopened bracket: %c\n", line_no, c2);
  else if (c2 == '\0')
    printf("%zu: unclosed bracket: %c\n", line_no, c1);
  else
    printf("%zu: bracket mismatch: %c and %c\n", line_no, c1, c2);
}


char pairof(char c)
{
  char z = c;
  switch (c) {
    case '(':
      z = ')';
      break;
    case ')':
      z = '(';
      break;
    case '[':
      z = ']';
      break;
    case ']':
      z = '[';
      break;
    case '{':
      z = '}';
      break;
    case '}':
      z = '{';
      break;
  }
  return z;
}


size_t check_paren(FILE* f)
{
  size_t line_no = 1;
  bool saw_squote = false,
       saw_dquote = false;
  char c;

  while ((c = fgetc(f)) != EOF) {
    if (c == '\'')
      saw_squote = !saw_squote;
    else if (c == '\"')
      saw_dquote = !saw_dquote;
    else if (saw_squote || saw_dquote)
      continue;

    switch (c) {
      case '(':
      case '[':
      case '{':
        stack[t++] = c;
        break;
      case ')':
      case ']':
      case '}':
        if (t > 0) {
          if (pairof(c) == stack[t - 1])
            stack[t--] = '\0';
          else
            call_error(line_no, stack[t - 1], c);
        } else call_error(line_no, '\0', c);
        break;
      case '\n':
        line_no++;
        break;
      default:
        break;
    }
  }
  if (t == 0) {
    printf("Ok.\n");
    return EXIT_SUCCESS;
  } else {
    call_error(line_no, stack[t - 1], '\0');
    return EXIT_FAILURE;
  }
}


int main(int argc, char **argv)
{
  if (argc != 2) {
    printf("Usage: %s <file>\n", argv[0]);
    return 0;
  }

  printf("Program by Hathim Ali (No. 30)\n\n");

  FILE *f = fopen(argv[1], "r");
  size_t z = check_paren(f);
  fclose(f);

  return z;
}
