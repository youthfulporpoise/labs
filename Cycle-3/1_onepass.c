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

  unsigned length = 0;
  unsigned startaddr = 0;
  char progname[16];

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
      locctr = (unsigned) strtol(operand, NULL, 16);
      append(&symtab, label, locctr);
      startaddr = locctr;
      strcpy(progname, label);
      continue;
    }

    if (label != NULL) {
      if (lookup(symtab, label) >= 0) {
        printf("error: redefining label: %s\n", label);
        exit(10);
      } else append(&symtab, label, locctr);
    }

    if (strcmp(opcode, "WORD") == 0 || strcmp(opcode, "BYTE") == 0)
      sprintf(line_copy, "%s\n", operand);
    else if (strcmp(opcode, "RESW") == 0 || strcmp(opcode, "RESB") == 0)
      sprintf(line_copy, "\n");
    else if (tokc == 3 || tokc == 2)
      sprintf(line_copy, "%s %s\n", opcode, operand);

    sprintf(scratch, "%04zX %s", locctr, line_copy);

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
  printf("\n");

  /* * * * * * * * */
  /*    Pass 2.    */
  /* * * * * * * * */

  text_record tr = { .start = startaddr, .size = 0 };
  printf("H^%s^%06x^%06x\n", progname, startaddr, length);

  while ((line = strsep(&intermediate, "\n")) != NULL) {
    if (tr.size == 10) {
      print_text_record(&tr);
      continue;
    }

    label = NULL;
    opcode = NULL;
    operand = NULL;
    tokc = parse_line_2(line, strlen(line), &label, &opcode, &operand);
   
    if (operand != NULL)
      sprintf(tr.record[tr.size], "%02X%04X",
        optab.value[lookup(optab, opcode)],
        symtab.value[lookup(symtab, operand)]
      );
    else if (opcode != NULL)
      sprintf(tr.record[tr.size], "%06lX",
        strtol(opcode, NULL, 16)
      );
    else continue;

    tr.size++;
  };
  print_text_record(&tr);
  printf("E^%X\n", startaddr);

  return 0;
}
