#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main (int, char**);
void push (int);
int pop ();
void display ();

int* stack;
size_t top = 0;

int main(int argc, char** argv)
{
    if (argc != 2) {
        puts("Provide the size of stack.");
        return 1;
    }

    size_t size;
    if (sscanf(argv[1], "%zu", &size) != 1) {
        puts("Not a valid size.");
        return 1;
    }
    stack = calloc(size, sizeof (int));

    char choice;
    while (true) {
        printf("(1) Push  (2) Pop  (3) Display  (q) Quit\nChoice: ");
        scanf(" %c", &choice);
        puts("");
        switch (choice) {
            case '1': {
                int x;
                if (top >= size) puts("The stack is full.");
                else {
                    printf("Element: "); scanf("%d", &x);
                    push(x);
                } break;
            }
            case '2':
                if (top == 0) puts("The stack is empty.");
                else printf("Element: %d\n", pop());
                break;
            case '3':
                display();
                break;
            case 'q':
                return 0;
            default:
                printf("%c is not a valid choice.\n", choice);
                break;
        }
        puts("");
    }

    return 0;
}

void push(int x) { stack[top++] = x; }
int pop() { return stack[--top]; }
void display()
{
    printf("Stack: ");
    if (top == 0) puts("-/-");
    else {
        for (size_t i = top; i > 0;) printf("%d ", stack[--i]);
        puts("");
    }
}

