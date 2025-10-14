/*  sic.h
 *  *****
 *  These are the internal functions used by the one-pass and two-pass
 *  assemblers of the SIC machine.  These include the optab, symtab, and other
 *  such auxiliary functions as may be required throughout the course of
 *  implementation.
 */

/* * * * * * * * * * * * * */
/*    DATA STRUCTURES      */
/* * * * * * * * * * * * * */

#define       CHARINTMAP_MAX        256

typedef struct {
  char *key[CHARINTMAP_MAX];
  int value[CHARINTMAP_MAX];
  size_t size;
} char_int_map;

/*  OPCODE TABLE  */
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
  .size = 24
};

/*  SYMBOL TABLE  */
char_int_map symtab;

/*  TEXT RECORD   */
typedef struct {
  size_t start;
  size_t size;
  char record[16][10];
} text_record;


/* * * * * * * * * * * * * * * */
/*    AUXILIARY FUNCTIONS      */
/* * * * * * * * * * * * * * * */

/*  define_str creates a dynamically allocated string that lives throughout the
 *  lifespan of the program.  We do not want strings to be destructed every time
 *  it goes out of scope.
 */

char *define_str(char *src)
{
  char *dst = malloc(strlen(src));
  strcpy(dst, src);
  return dst;
}

/*  lookup returns the corresponding index of the input key if it exists in
 *  the key-value mapping, -1 otherwise.
 */

ssize_t lookup(char_int_map map, char *key)
{
  for (size_t i = 0; i < map.size; ++i) {
    if (strcmp(map.key[i], key) == 0)
      return i;
  }
  return -1;
}

/*  set_value is an convenient abstraction that could also be plausibly be done
 *  manually with lookup function.  It simply finds *key and sets val as the
 *  corresponding value.
 */

ssize_t set_value(char_int_map map, char *key, int val)
{
  int i = lookup(map, key);
  if (i < 0) return -1;
  else {
    map.value[i] = val;
    return 0;
  }
}

/*  append, as suggested by its name, adds an entry to end of the key-value
 *  mapping unless the maximum size allowed of the key-value is exceeded.
 */

void append(char_int_map *map, char *key, int val)
{
  if (map->size != CHARINTMAP_MAX) {
    map->key[map->size] = define_str(key);
    map->value[map->size] = val;
    map->size++;
  }
}

/*  count_tokens is an abstraction to accurately count the tokens in a string.
 *  This is required since we are using strsep instead of strtok (†).  It
 *  handles the case of adjacent delmiters and returns the exact number of
 *  tokens in every case.
 */

size_t count_tokens(char *str, size_t len, char delim)
{
  bool was_prev_delim = false;
  size_t count = 0;
  for (size_t i = 0; i < len; ++i) {
    if (str[i] != delim) {
      if (!was_prev_delim) {
        was_prev_delim = true;
        count++;
      }
    } else was_prev_delim = false;
  }
  return count;
}

/*  next_token solves the issue that arises when more than one delimiters are
 *  adjacent in the string of concern. The string is checked whether it is empty
 *  and only returned otherwise.
 */

char *next_token(char **lref, char *delim)
{
  char *tok;
  // while (*(tok = strsep(lref, delim)) == '\0' || strlen(tok) == 0);
  while (strlen(tok = strsep(lref, delim)) == 0);
  return tok;
}

/*  parse_line parses the line into the fields **label, **opcode, **operand,
 *  with respect to the number of tokens in the line.  The parsing proceeds in
 *  this manner:
 *
 *  +-------------+------------------------------------------------+
 *  | token count | parse                                          |
 *  +-------------+------------------------------------------------+
 *  | 1           | label = NULL   opcode = #1   operand = NULL    |
 *  | 2           | label = NULL   opcode = #1   operand = #2      |
 *  | 3           | label = #1     opcode = #2   operand = #3      |
 *  +-------------+------------------------------------------------+
 */

size_t parse_line_1(char *lref, size_t len, char **label, char **opcode, char **operand)
{
  size_t tokc = count_tokens(lref, len, ' ');
  char delim[] = " \n\t";

  *label = NULL;
  *opcode = NULL;
  *operand = NULL;

  switch (tokc) {
    case 1:
      *opcode = next_token(&lref, delim);
      break;
    case 2:
      *opcode = next_token(&lref, delim);
      *operand = next_token(&lref, delim);
      break;
    case 3:
      *label = next_token(&lref, delim);
      *opcode = next_token(&lref, delim);
      *operand = next_token(&lref, delim);
      break;
  }
  return tokc;
}

/*  +-------------+------------------------------------------------+
 *  | token count | parse                                          |
 *  +-------------+------------------------------------------------+
 *  | 1           | label = #1     opcode = NULL  operand = NULL   |
 *  | 2           | label = #1     opcode = #2    operand = NULL   |
 *  | 3           | label = #1     opcode = #2    operand = #3     |
 *  +-------------+------------------------------------------------+
 */

size_t parse_line_2(char *lref, size_t len, char **loc, char **opcode, char **operand)
{
  size_t tokc = count_tokens(lref, len, ' ');
  char delim[] = " \t\n";

  *loc = NULL;
  *opcode = NULL;
  *operand = NULL;

  switch (tokc) {
    case 1:
      *loc = next_token(&lref, delim);
      break;
    case 2:
      *loc = next_token(&lref, delim);
      *opcode = next_token(&lref, delim);
      break;
    case 3:
      *loc = next_token(&lref, delim);
      *opcode = next_token(&lref, delim);
      *operand = next_token(&lref, delim);
      break;
  }
  return tokc;
}

/*  print_mapping prints the contents of the given map as key-value pairs
 *  line-by-line.
 */

void print_mapping(char_int_map map)
{
  for (size_t i = 0; i < map.size; ++i)
    printf("%04X <- %-8s\n", map.value[i], map.key[i]);
}

/*  print the text record, including the carets for distinction, the starting
 *  address, and the length of the record.
 */

void print_text_record(text_record *tr)
{
  if (tr->size == 0) return;

  printf("T^%06zX^%02zX", tr->start, tr->size * 3);
  for (size_t i = 0; i < tr->size; ++i)
    printf("^%s", tr->record[i]);
  printf("\n");

  tr->start += tr->size;
  tr->size = 0;
}
