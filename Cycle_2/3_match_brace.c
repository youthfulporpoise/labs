#include <stdio.h>

#define STACK_SIZE 512
char stack[STACK_SIZE];
size_t top = 0;
void push(char x) { stack[top++] = x; }
char pop() { return stack[--top]; }

char pair (char);

int main(int argc, char**argv)
{
    if (argc != 2) {
        puts("argument: one and only one at a time");
        return 1;
    }
    FILE* f = fopen(argv[1], "r");
    char c;
    while ((c = fgetc(f)) != EOF) {
        if (c == '(' || c == '[' || c == '{') {
            if (top < STACK_SIZE) push(c);
            else {
                printf("stack overflow: %d\n", STACK_SIZE);
                return 2;
            }
        } else if (c == ')' || c == ']' || c == '}') {
            if (top == 0) {
                printf("bracket mismatch: missing %c\n", c);
                return 0;
            } else {
                if (pop() != pair(c)) {
                    printf("bracket mismatch: missing %c\n", pair(c));
                    return 0;
                } else continue;
            }
        } else continue;
    } puts("bracket match: ok");
    fclose(f);
    return 0;
}

char pair(char c) {
    switch (c) {
        case '(': return ')';
        case '[': return ']';
        case '{': return '}';
        case ')': return '(';
        case ']': return '[';
        case '}': return '{';
    }
}
