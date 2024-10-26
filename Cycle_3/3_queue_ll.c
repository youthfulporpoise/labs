#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* BEGIN: queue definitions */
typedef struct node Node;
typedef struct node {
    char data;
    Node* next;
} Node;

Node* ll = NULL;

void enqueue(char c)
{
    Node* x = malloc(sizeof (Node));
    x->data = c; x->next = NULL;
    if (ll == NULL) ll = x;
    else {
        Node* p = ll;
        while (p->next != NULL) p = p->next;
        p->next = x;
    }
}

char dequeue()
{
    if (ll == NULL) {
        puts("Queue Underflow");
        return '\0';
    } else {
        Node* p = ll; ll = p->next;
        char c = p->data; free(p);
        return c;
    }
}

void display()
{
    printf("Data: ");
    if (ll == NULL) puts("-/-");
    else {
        Node* p = ll;
        while (p->next != NULL) {
            printf("%c -> ", p->data);
            p = p->next;
        } printf("%c\n", p->data);
    }
}
/* END: queue definitions */

int main()
{
    char choice;
    puts("(1) Enqueue  (2) Dequeue  (3) Display  (q) Quit");
    while (true) {
        printf("Choice: "); scanf(" %c", &choice);
        /* These are variables that might be used. */
        char input;
        switch (choice) {
            case '1':
                printf("Character: "); scanf(" %c", &input);
                enqueue(input);
                break;
            case '2':
                printf("Dequeued: %c\n", dequeue());
                break;
            case '3':
                display();
                break;
            case 'q':
                return 0;
            default:
                printf("%c: invalid choice\n", choice);
                continue;
        } puts("");
    }
}
