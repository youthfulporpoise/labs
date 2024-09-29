#include <stdio.h>
#include <ctype.h>

char o[128]; size_t to = 0; /* for operators. */
char r[128]; size_t tr = 0; /* for operand and result.  */

int main ();
int prec (char);

int main()
{
    printf(" Infix: ");
    char c;
    while (!isspace(c = fgetc(stdin))) {
        o[to] = '\0';
        printf("%16s  %2zu\t%16s  %2zu\t%c\n", r, tr, o, to, c);
        if (isalnum(c)) r[tr++] = c;
        else if (c == '(') o[to++] = '(';
        else if (c == ')') {
            while ((c = o[--to]) != '(') {
                if (to == 0) {
                    fprintf(stderr, "error: bracket mismatch: missing (\n");
                    return 1;
                } r[tr++] = c;
            }
        } else {
            if (to == 0) o[to++] = c;
            else if (prec(c) > prec(o[to - 1])) o[to++] = c;
            else {
                while (to != 0 && o[to - 1] != '(' && prec(c) <= prec(o[to - 1]))
                    r[tr++] = o[--to];
                o[to++] = c;
            }
        }
    } while (to != 0) {
        if (o[to - 1] == '(') {
            fprintf(stderr, "error: bracket mismatch: missing )\n");
            return 1;
        } r[tr++] = o[--to];
    }
    printf("Postfix: %s\n", r);
    return 0;
}

int prec(char x)
{
    int v;
    if (x == '+' || x == '-') v = 0;
    else if (x == '*' || x == '/') v = 1;
    else if (x == '^') v = 2;
    else if (x == '(') v = -1;
    return v;
}
