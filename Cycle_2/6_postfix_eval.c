#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

int r[128]; size_t tr = 0;

int main()
{
    printf("Postfix: ");
    char c;
    while (!isspace(c = fgetc(stdin))) {
        if (isdigit(c)) r[tr++] = atoi(&c); 
        else {
            if (tr < 2) {
                fprintf(stderr, "incomplete arguments: %c\n", c);
                return 1;
            }
            int x, y;
            switch (c) {
                case '+':
                    y = r[--tr]; x = r[--tr];
                    r[tr++] = x + y;
                    break;
                case '-':
                    y = r[--tr]; x = r[--tr];
                    r[tr++] = x - y;
                    break;
                case '*':
                    y = r[--tr]; x = r[--tr];
                    r[tr++] = x * y;
                    break;
                case '/':
                    y = r[--tr]; x = r[--tr];
                    r[tr++] = x / y;
                    break;
                case '^':
                    y = r[--tr]; x = r[--tr];
                    r[tr++] = x ^ y;
                    break;
                case '%':
                    y = r[--tr]; x = r[--tr];
                    r[tr++] = x & y;
                    break;
                default:
                    fprintf(stderr, "invalid operator/function: %c\n", c);
                    return 1;
            }
        }
    }
    if (tr != 1) {
        fprintf(stderr, "superfluous arguments: ");
        --tr;
        while (tr != 0)
            fprintf(stderr, "%d ", r[--tr]);
        fputc('\n', stderr);
        return 1;
    } printf("Evaluation: %d\n", r[--tr]);
    return 0;
}
