#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define       STKSZ       128


size_t check_loop(FILE *f)
{
  char c;
  size_t line_no = 0;
  int state = 0;

  char stack[STKSZ];
  size_t t = 0;

  while ((c = fgetc(f)) != EOF) {
    if (c == '\n')
      line_no++;

    if ((c == ' ' || c == '\n') && state == 0)
      state = 1;
    else if (c == 'f' && state == 1)
      state = 2;
    else if (c == 'o' && state == 2)
      state = 3;
    else if (c == 'r' && state == 3)
      state = 4;
    else if (state == 4) {
      if (c == '(')
        state = 5;
      else if (c == ' ')
        continue;
      else
        return line_no;
    }
    else if (c == ';' && state == 5)
      state = 6;
    else if (c == ';' && state == 6)
      state = 7;
    else if (state == 7) {
      if (c == '(')
        stack[t++] = '(';
      else if (c == ')') {
        if (t == 0)
          state = 0;
        else
          stack[--t] = '\0';
      }
      else
        continue;
    }
    else if (state < 3)
      state = 0;
  }

  if (state > 2)
    return line_no;
  else
    return 0;
}


int main(int argc, char **argv)
{
  if (argc != 2) {
    printf("%s <input file>\n", argv[0]);
    return 0;
  }

  size_t z;
  FILE *f = fopen(argv[1], "r");
  z = check_loop(f);
  fclose(f);

  if (z)
    printf("%zu: broken for loop\n", z);
  else
    printf("Ok.\n");

  return (z > 0 ? 1 : 0);
}
