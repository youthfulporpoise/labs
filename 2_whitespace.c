#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct stat {
  char c0;
  char c1;
  char c2;

  bool in_string;
  bool in_comment;
  bool in_comment_mult;
};


char shift_head(struct stat *st, FILE *f)
{
  st->c2 = st->c1;
  st->c1 = st->c0;
  st->c0 = fgetc(f);

  return st->c0;
}


int main(int argc, char **argv)
{
  if (argc != 3) {
    printf("%s <input file> <output file>\n", argv[0]);
    return 0;
  }

  FILE *ipf = fopen(argv[1], "r");
  FILE *opf = fopen(argv[2], "w");

  struct stat st = {
    .c0 = EOF,
    .c1 = 0,
    .c2 = 0,
    .in_string = false,
    .in_comment = false,
    .in_comment_mult = false
  };

  shift_head(&st, ipf);
  while (shift_head(&st, ipf) != EOF) {
    /* We look and set states here. */
    switch (st.c1) {
      case '/':
        if (st.c0 == '/')
          st.in_comment = true;
        else if (st.c0 == '*')
          st.in_comment_mult = true;
        break;
      case '*':
        if (st.c0 == '/')
          st.in_comment_mult = false;
        break;
      case '"':
        st.in_string = !st.in_string;
        break;
      case '\n':
        st.in_comment = false;
        break;
    }

    /* Ignore whitespaces. */
    switch (st.c1) {
      case ' ':
      case '\n':
      case '\t':
        if (st.in_string)
          fputc(st.c1, opf);
        break;
      default:
        if (!st.in_comment && !st.in_comment_mult)
          fputc(st.c1, opf);
    }
  }

  

  fclose(ipf);
  fclose(opf);

  return 0;
}
