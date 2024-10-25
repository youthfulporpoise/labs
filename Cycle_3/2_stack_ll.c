#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* BEGIN: linked list definitions */
typedef struct node Node;
typedef struct node {
    char data;
    Node* next;
} Node;

Node* ll = NULL;

void push(char c)
{
    Node* x = malloc(sizeof (Node)); x->data = c;
    x->next = ll; ll = x;
}

char pop()
{
    if (ll == NULL) {
        puts("Stack Underflow");
        return '\0';
    }
    Node* x = ll; ll = ll->next;
    char c = x->data; free(x);
    return c;
}

void display()
{
    Node* p = ll;
    printf("Stack: ");
    if (p == NULL) { puts("-/-"); return; }
    while (p->next != NULL) {
        printf("%c -> ", p->data);
        p = p->next;
    } printf("%c\n", p->data);
}
/* END: linked list definitions */

int main()
{
    char choice;
    while (true) {
        printf("(1) Push  (2) Pop  (3) Display  (q) Quit\nChoice: ");
        scanf(" %c", &choice);
        /* These variables that may be used inside the switch-case. */
        char input;
        switch (choice) {
            case '1':
                printf("Character: "); scanf(" %c", &input);
                push(input);
                break;
            case '2':
                printf("Popped: %c\n", pop());
                break;
            case '3':
                display();
                break;
            case 'q':
                return 0;
            default:
                printf("%c: invalid choice\n", choice);
                continue;
        }
        puts("");
    }
}
