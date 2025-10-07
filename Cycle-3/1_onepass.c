#include  <stdio.h>
#include  <stdlib.h>
#include  <stdbool.h>
#include  <string.h>
#include  "sic.h"

int main(int argc, char **argv)
{
  FILE *file;
  if (argc != 2) {
    printf("Usage: %s <sic source>\n", argv[0]);
    return 0;
  } else file = fopen(argv[1], "r");

  size_t tokc;
  char *line = malloc(256);
  char line_copy[256];
  char *label, *opcode, *operand;

  unsigned length;
  unsigned startaddr;
  char *progname;

  char scratch[256];
  char *intermediate = calloc(1024, sizeof (char));
  char output[1024]; 

  /* * * * * * * * */
  /*    Pass 1.    */
  /* * * * * * * * */

  size_t locctr = 0;

  while (fgets(line, 256, file) != NULL) {
    strcpy(line_copy, line);
    tokc = parse_line_1(line, strlen(line), &label, &opcode, &operand);

    if (strcmp(opcode, "END") == 0)
      break;

    if (strcmp(opcode, "START") == 0) {
      locctr = (unsigned) strtol(operand, NULL, 10);
      startaddr = locctr;
      progname = label;
      continue;
    }

    if (label != NULL) {
      if (lookup(symtab, label) >= 0) {
        printf("error: redefining label: %s\n", label);
        exit(10);
      } else
        append(&symtab, label, locctr);
    }

    if (strcmp(opcode, "WORD") == 0 || strcmp(opcode, "BYTE") == 0)
      sprintf(line_copy, "%s\n", operand);
    else if (strcmp(opcode, "RESW") == 0 || strcmp(opcode, "RESB") == 0)
      sprintf(line_copy, "\n");
    else if (tokc == 3)
      sprintf(line_copy, "%s %s\n", opcode, operand);

    sprintf(scratch, "%04zu %s", locctr, line_copy);

    if (lookup(optab, opcode) >= 0)
      locctr += 3;
    else if (strcmp(opcode, "WORD") == 0)
      locctr += 3;
    else if (strcmp(opcode, "RESW") == 0)
      locctr += 3 * (unsigned) strtoll(operand, NULL, 10);
    else if (strcmp(opcode, "RESB") == 0)
      locctr += (unsigned) strtoll(operand, NULL, 10);
    else if (strcmp(opcode, "BYTE") == 0) 
      locctr += strlen(operand);
    else {
      printf("error: unrecognized instruction: %s\n", opcode);
      exit(10);
    }

    strcat(intermediate, scratch);
  }
  length = locctr - startaddr;
  fclose(file);

  printf("%s\n", intermediate);
  print_mapping(symtab);

  text_record tr = { .start = 0, .size = 0 };
  sprintf(output, "H^%s^%06x^%06x\n", progname, startaddr, length);

  while ((line = strsep(&intermediate, "\n")) != NULL) {
    tokc = parse_line_2(line, strlen(line), &label, &opcode, &operand);

    printf("%02zx%04zx", lookup(optab, opcode), lookup(symtab, operand));
    if (tr.size == 10) {
      tr.start += tr.size;
      tr.size = 0;
      print_text_record(tr);
    }

    switch (tokc) {
      case 1:
        sprintf(tr.record[tr.size], "^xxxxxx");
        break;
      case 2:
        sprintf(tr.record[tr.size], "%06lx", strtol(operand, NULL, 10));
        break;
      case 3:
        sprintf(tr.record[tr.size], "%02zx%04zx", lookup(optab, opcode),
          lookup(symtab, operand));
        break;
    }
    
    sprintf(tr.record[tr.size], "%02zx%04zx",
      lookup(optab, opcode), lookup(symtab, operand));
    tr.size++;
  };

  return 0;
}
