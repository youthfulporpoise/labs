#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char **argv)
{
  if (argc != 2) {
    printf("%s <object file>\n", argv[0]);
    return 0;
  }

  char *record = malloc(256),
       *token;
  size_t locctr = 0,
         rec_per_line = 4,
         rec_count = 4;
  unsigned null;

  FILE *file = fopen(argv[1], "r");
  printf("MEMORY");

  while (fgets(record, 256, file) != NULL) {
    if (record[0] == 'H') {
      for (size_t i = 0; i < 3; ++i)
        token = strsep(&record, "^");
      sscanf(token, "%zX", &locctr);
    } else if (record[0] == 'T') {
      size_t i = 12;
      while (record[i] != '\0') {
        if (rec_count == rec_per_line) {
          rec_count = 0;
          printf("\n%zX  ", locctr);
          locctr += 24;
        }
        if (record[i] == '^' || record[i] == '\n') {
          printf("  ");
          i++;
          rec_count++;
        } else printf("%c", record[i++]);
      }
    }
  }
  printf("\n");

  fclose(file);

  return 0;
}
