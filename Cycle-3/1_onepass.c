#include  <stdio.h>
#include  <stdlib.h>
#include  <stdbool.h>
#include  <string.h>

#define   INTRMLEN    1024
#define   SCRCHLEN    256
#define   LINELEN     (32 * 3)
#define   WORDLEN     32
#define   OBJCTLEN    1024

typedef struct {
  char key[32][16];
  long value[32];
  size_t n;
} char_int_map;

char_int_map optab = {
  .key = {
    "ADD", "AND", "COMP", "DIV", "J", "JEQ", "JGT", "JLT", "JSUB", "LDA",
    "LDCH", "LDL", "LDX", "MUL", "OR", "RD", "RSUB", "STA", "STCH", "STL",
    "STX", "SUB", "TD", "TIX", "WD"
  },
  .value = {
    0x18, 0x40, 0x28, 0x24, 0x3C, 0x30, 0x34, 0x38, 0x48, 0x00, 0x50, 0x08,
    0x04, 0x20, 0x44, 0xD8, 0x4C, 0x0C, 0x54, 0x14, 0x10, 0x1C, 0xE0, 0x2C, 0xDC
  },
  .n = 24
};

char_int_map symtab = { .n = 0 };

bool lookup(char *key, char_int_map map) {
  for (size_t i = 0; i < map.n; i++)
    if (strcmp(key, map.key[i]) == 0)
      return true;
  return false;
}

long getvalue(char *key, char_int_map map) {
  for (size_t i = 0; i < map.n; i++)
    if (strcmp(key, map.key[i]) == 0)
      return map.value[i];
  return -1;
}

char object[OBJCTLEN] = "\0",
     txtrec[SCRCHLEN] = "\0",
     tmp[SCRCHLEN];

void write_hdr(char *prgname, unsigned long begaddr, unsigned long prglen)
{
  sprintf(tmp, "H^%s^%06lX^%06lX\n", prgname, begaddr, prglen);
  strcat(object, tmp);
}

void write_txt(unsigned long begaddr, char *opcode, char *operand, bool forcewr)
{
  static size_t txtreccnt = 0;
  static size_t txtreclen = 0;
  static size_t recbegaddr;
  static size_t recbegaddr_init = false;

  if (!recbegaddr_init) {
    recbegaddr = begaddr;
    recbegaddr_init = true;
  }

  if (txtreccnt == 10 || forcewr) {
    sprintf(tmp, "T^%06lX^%02lX%s\n", recbegaddr, txtreclen, txtrec);
    strcat(object, tmp);

    recbegaddr += txtreclen;
    txtreccnt = 0;
    txtreclen = 0;
    sprintf(txtrec, "");
    sprintf(tmp, "");
  }

  if (strcmp(opcode, "WORD") == 0)
    sprintf(tmp, "^%06lX", strtol(operand, NULL, 10));
  else if (strcmp(opcode, "RESB") == 0)
    sprintf(tmp, "^xxxxxx");
  else if (strcmp(opcode, "RESW") == 0)
    sprintf(tmp, "^xxxxxx");
  else
    sprintf(tmp, "^%02lX%04lX",
      getvalue(opcode, optab),
      getvalue(operand, symtab)
    );

  strcat(txtrec, tmp);
  txtreccnt++;
  txtreclen += 6;
}

void write_end(unsigned long begaddr)
{
  sprintf(tmp, "E^%06lX\n", begaddr);
  strcat(object, tmp);
}

int main(int argc, char **argv)
{
  if (argc != 2) {
    fprintf(stdout, "Usage: %s <sic source>\n", argv[0]);
    return 255;
  }

  FILE *file = fopen(argv[1], "r");
  
  char line[LINELEN];
  char a[WORDLEN], b[WORDLEN], c[WORDLEN];
  char scratch[SCRCHLEN];
  size_t tokc;
  size_t lineno = 1;
  unsigned long begaddr = 0;
  unsigned long prglen = 0;

  unsigned long locctr = 0;
  char *label, *opcode, *operand;
  char intermediate[INTRMLEN] = "\0";

  /* * * * * * */
  /*  PASS  1  */
  /* * * * * * */

  while (fgets(line, LINELEN, file) != NULL) {
    lineno++;
    tokc = sscanf(line, " %s %s %s", a, b, c);
    switch (tokc) {
        case 3:
          label = a;
          opcode = b;
          operand = c;
          break;
        case 2:
          label = NULL;
          opcode = a;
          operand = b;
          break;
        case 1:
          label = NULL;
          opcode = a;
          operand = NULL;
          break;
        default:
          fprintf(stderr, "error: invalid instruction: line %zu\n", lineno);
          return 120;
    }

    if (label != NULL) {
      if (lookup(label, symtab) == true) {
        fprintf(stderr, "error: redefining label: %s\n", label);
        return 100;
      } else {
        strncpy(symtab.key[symtab.n], label, WORDLEN);
        symtab.value[symtab.n] = locctr;
        symtab.n++;
      }
    }

    if (strcmp(opcode, "START") == 0) {
      locctr = strtol(operand, NULL, 16); 
      begaddr = locctr;
      continue;
    } else if (strcmp(opcode, "END") == 0)
      break;

    sprintf(scratch, "%04lX %8s %8s %8s\n",
      locctr, label ? label : "*",
      opcode, operand
    );

    if (lookup(opcode, optab) == true)
      locctr += 3;
    else if (strcmp(opcode, "WORD") == 0)
      locctr += 3;
    else if (strcmp(opcode, "RESW") == 0)
      locctr += strtol(operand, NULL, 10) * 3;
    else if (strcmp(opcode, "RESB") == 0) {
      long val = strtol(operand, NULL, 10);
      locctr += 6 * (val / 6 + 1);
    }
    else if (strcmp(opcode, "BYTE") == 0)
      locctr += strlen(operand);
    else {
      fprintf(stderr, "error: invalid opcode: %s\n", opcode);
      return 110;
    }

    strcat(intermediate, scratch);
  }

  prglen = locctr - begaddr;
  fprintf(stdout, "Program Length %04lX\n", prglen);

  fprintf(stdout, "%s", intermediate);
  fprintf(stdout, "\n");
  for (size_t i = 0; i < symtab.n; ++i)
    fprintf(stdout, "%-8s : %04lX\n", symtab.key[i], symtab.value[i]);
  fclose(file);

  /* * * * * * */
  /*  PASS  2  */
  /* * * * * * */

  file = fmemopen(intermediate, strlen(intermediate), "r");
  lineno = 1;
  tokc = 0;

  label = malloc(WORDLEN);
  opcode = malloc(WORDLEN);
  operand = malloc(WORDLEN);
  locctr = 0;

  write_hdr(symtab.key[0], begaddr, prglen);
  while (fgets(line, LINELEN, file) != NULL) {
    tokc = sscanf(line, "\n %04lX %s %s %s", &locctr, label, opcode, operand);
    if (strcmp(opcode, "RESB") == 0) {
      long val = strtol(operand, NULL, 10);
      for (size_t i = 0; i < val; i += 6)
        write_txt(begaddr, opcode, operand, false);
    } else if (strcmp(opcode, "RESW") == 0) {
      long val = strtol(operand, NULL, 10);
      for (size_t i = 0; i < val; ++i)
        write_txt(begaddr, opcode, operand, false);
    } else
      write_txt(begaddr, opcode, operand, false);
  }
  write_txt(begaddr, opcode, operand, true);
  write_end(begaddr);

  fprintf(stdout, "\n%s", object);
  free(label); free(opcode); free(operand);
  return 0;
}
