#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

int main(int argc, char **argv)
{
  if (argc != 2) {
    printf("%s <object file>\n", argv[0]);
    return 0;
  }

  char record[256];
  long begaddr, prglen;
  long bytecnt = 0;

  FILE *file = fopen(argv[1], "r");

  fprintf(stdout, "MEMORY\r");
  while (fgets(record, 256, file) != NULL) {
    if (record[0] == 'H') {
      size_t i = 0;
      while (isalpha(record[i]) || record[i] == '^')
        i++;
      sscanf(&record[i], "%06lX^%06lX", &begaddr, &prglen);
    } else if (record[0] == 'T') {
      for (size_t i = 12; i < strlen(record); i += 2) {
        if (record[i] == '^')
          i++;
        else if (record[i] == '\n')
          continue;

        if (bytecnt % 12 == 0) {
          fprintf(stdout, "\n%04lX", begaddr);
          begaddr += 12;
        }

        if (bytecnt % 3 == 0)
          fprintf(stdout, "\t");

        fprintf(stdout, "%c%c", record[i], record[i + 1]);
        bytecnt++;
      }
    }
  }
  printf("\n");

  fclose(file);

  return 0;
}
