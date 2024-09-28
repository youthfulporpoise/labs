#include <stdio.h>
#include <ctype.h>

char o[512]; size_t to = 0; /* for operators. */
char r[512]; size_t tr = 0; /* for operand and result.  */

int main ();
int prec (char);

int main()
{
    printf(" Infix: ");
    char c;
    while (!isspace(c = fgetc(stdin))) {
        if (isalnum(c)) r[tr++] = c;
        else if (c == ')') {
            while ((c = o[--to]) != '(') r[tr++] = c;
        } else {
            if (to == 0) o[to++] = c;
            else {
                if (prec(c) > prec(o[to - 1])) o[to++] = c;
                else { while(to != 0) r[tr++] = o[--to]; o[to++] = c; }
            }
        }
    } while (to != 0) r[tr++] = o[--to];
    printf("Postfix: : %s\n", r);
    return 0;
}

int prec(char x) {
    int v;
    if (x == '+' || x == '-') v = 0;
    else if (x == '*' || x == '/') v = 1;
    else if (x == '^') v = 2;
    return v;
}
