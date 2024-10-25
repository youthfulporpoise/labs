#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    char data;
    struct node* next;
} Node;
Node* ll = NULL;

void create()
{
    ll = malloc(sizeof (Node));
    ll->next = NULL;
}

void insert(size_t pos, Node* x)
{
    Node* curr = ll, *last = NULL;
    pos += 1;
    while (pos > 0) {
        if (curr->next == NULL) {
            puts("Reached NULL node before position.");
            puts("Aborting ...");
            return;
        } else { last = curr; curr = curr->next; pos--; }
    } last->next = x;  x->next = curr;
    return;
}

void append(Node* x)
{
    Node* p = ll;
    while (p->next != NULL) p = p->next;
    x->next = NULL; p->next = x;
}

char delete(size_t pos)
{
    Node *curr = ll, *last = NULL, *next = NULL;
    pos++;
    while (pos > 0) {
        if (curr->next == NULL) {
            puts("Reached NULL node before position.");
            puts("Aborting ...");
            return '\0';
        } else { last = curr; curr = curr->next; pos--; }
    }
    last->next = curr->next;
    char c = curr->data; free(curr);
    return c;
}

void display()
{
    printf("Data: ");
    Node *p = ll;
    if (p->next == NULL) { puts("-/-"); return; }
    while (p->next->next != NULL) {
        p = p->next;
        printf("%c -> ", p->data);
    } printf("%c\n", p->next->data);
    return;
}

int main()
{
    /* Initialize the linked list once. */
    create();
    char choice;
    while (true) {
        printf("(1) Append  (2) Insert  (3) Delete  (4) Display  (q) Quit\nChoice: ");
        scanf(" %c", &choice);
        /* These are variables that might be used. */
        char input; size_t pos; Node* x;
        switch (choice) {
            case '1':  /* Append */
                printf("Character: "); scanf(" %c", &input);
                x = malloc(sizeof (Node)); x->data = input;
                append(x);
                break;
            case '2': /* Insert */
                printf("Character, Position: "); scanf(" %c %zu", &input, &pos);
                x = malloc(sizeof (Node)); x->data = input;
                insert(pos, x);
                break;
            case '3': /* Delete */
                printf("Position: "); scanf(" %zu", &pos);
                printf("%c: deleted\n", delete(pos));
                break;
            case '4': /* Display */
                display();
                break;
            case 'q': /* Quit */
                return 0;
            default: /* Invalid choice */
                printf("%c: invalid choice\n", choice);
                continue;
        }
        puts("");
    }
}
