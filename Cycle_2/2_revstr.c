#include <stdio.h>

char stack[128];
size_t top = 0;
void push(char x) { stack[top++] = x; }
char pop() { return stack[--top]; }

int main(int argc, char**argv)
{
    char c;
    printf("String: ");
    while ((c = fgetc(stdin)) != '\n') push(c);

    printf("Result: ");
    while (top != 0) fputc(pop(), stdout);
    fputc('\n', stdout);
    return 0;
}
