#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* DOUBLY-LINKED LIST DEFINITIONS */
typedef struct node Node;
typedef struct node {
    char data;
    Node* prev;
    Node* next;
} Node;

Node* head = NULL;
Node* foot = NULL;

void link(Node* q, Node* p, Node* r)
/* This is an internal routine used by other more semantically
 * useful routines.  This routine adds q into the LL such that:
 * [...] -> p -> q -> r -> [...] */
{
    if (p == NULL) head = q; else p->next = q;
    if (r == NULL) foot = q; else r->prev = q;
    q->prev = p; q->next = r;
}

void insert(size_t pos, Node* q)
{
    Node* p = head; Node* r = foot;
    while (pos > 0) {
        if (p == NULL) {
            printf("%zu: does not exist.", pos);
            return;
        } else { p = p->next; pos--; }
    } link(q, p == NULL ? NULL : p->prev, p);
}

void append(Node* x)
{
    link(x, foot, NULL);
}

void prepend(Node* x)
{
    link(x, NULL, head);
}

char delink(Node* q)
/* This is an internal routine used by other more semantically
 * useful routines. */
{
    Node* p = q->prev; Node* r = q->next;
    if (p == NULL) head = r; else p->next = r;
    if (r == NULL) foot = p; else r->prev = p;
    char c = q->data; free(q);
    return c;
}

void delete_value(char v)
{
    Node* q = head;
    while (q != NULL) {
        if (q->data == v) printf("%c: deleted\n", delink(q));
        else q = q->next;
    }
    printf("%c: character does not exist\n", v);
    return;
}

void delete_position(size_t pos)
{
    Node* q = head;
    size_t i = pos;
    while (i > 0) {
        if (q != NULL) { q = q->next; i--; }
        else {
            printf("%zu: position does not exist\n", pos);
            return;
        }
    }
    if (q == NULL) printf("%zu: position does not exist\n", pos);
    else printf("%c: deleted\n", delink(q));
}

void display()
{
    Node* p = head;
    printf("Data Forward: ");
    if (p == NULL) puts("-/-");
    else {
        while (p->next != NULL) {
            printf("%c <=> ", p->data);
            p = p->next;
            if (p == NULL) break;
        } printf(" %c\n", p->data);
    }

    p = foot;
    printf("Data Reverse: ");
    if (p == NULL) puts("-/-");
    else { 
        while (p->prev != NULL) {
            printf("%c <=> ", p->data);
            p = p->prev;
        } printf(" %c\n", p->data);
    }
}
/* DOUBLY-LINKED LIST DEFINITIONS: END */

int main()
{
    char choice;
    puts("(1) Insert  (2) Append  (3) Prepend\n"
         "(4) Delete Value  (5) Delete Position\n"
         "(d) Display  (q) Quit\n");
    /* These are values that might be used inside the while-loop. */
    char value;
    size_t pos;
    Node* x;
    while (true) {
        printf("Choice: "); scanf(" %c", &choice);
        switch (choice) {
            case '1':
                printf("Character, Position: "); scanf(" %c %zu", &value, &pos);
                x = malloc(sizeof (Node)); x->data = value;
                insert(pos, x);
                break;
            case '2':
                printf("Character: "); scanf(" %c", &value);
                x = malloc(sizeof (Node)); x->data = value;
                append(x);
                break;
            case '3':
                printf("Character: "); scanf(" %c", &value);
                x = malloc(sizeof (Node)); x->data = value;
                prepend(x);
                break;
            case '4':
                printf("Character: "); scanf(" %c", &value);
                delete_value(value);
                break;
            case '5':
                printf("Position: "); scanf(" %zu", &pos);
                delete_position(pos);
                break;
            case 'd':
                display();
                break;
            case 'q':
                puts("Quitting ...");
                return 0;
            default:
                printf("%c: invalid choice\n", choice);
                continue;
        } puts("");
    }
}
