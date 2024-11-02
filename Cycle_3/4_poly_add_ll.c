#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int c;
    int p;
    struct node* next;
} Node;

Node* poly_1 = NULL;
Node* poly_2 = NULL;
Node* poly_0 = NULL;

Node* term(int c, int p)
{
    Node* x = malloc(sizeof (Node));
    x->c = c; x->p = p;
    return x;
}

Node* add_polynomials(Node* poly_1, Node* poly_2, Node* poly_0)
{
    Node* p1 = poly_1;
    Node* p2 = poly_2;
    Node* p0 = poly_0;

    while (p1 != NULL && p2 != NULL) {
        if (p1->p > p2->p) {
            if (p0 == NULL) poly_0 = p0 = term(p1->c, p1->p);
            else { p0->next = term(p1->c, p1->p); p0 = p0->next; }
            p1 = p1->next;
        } else if (p1->p < p2->p) {
            if (p0 == NULL) poly_0 = p0 = term(p2->c, p2->p);
            else { p0->next = term(p2->c, p2->p); p0 = p0->next; }
            p2 = p2->next;
        } else {
            if (p0 == NULL) poly_0 = p0 = term(p1->c + p2->c, p1->p);
            else { p0->next = term(p1->c + p2->c, p1->p); p0 = p0->next; }
            p1 = p1->next; p2 = p2->next;
        }
    } while (p1 != NULL) {
        if (p0 == NULL) p0 = term(p1->c, p1->p);
        else { p0->next = term(p1->c, p1->p); p0 = p0->next; }
        p1 = p1->next;
    } while (p2 != NULL) {
        if (p0 == NULL) p0 = term(p2->c, p2->p);
        else { p0->next = term(p2->c, p2->p); p0 = p0->next; }
        p2 = p2->next;
    }
    return poly_0;
}

Node* read_polynomial(char* msg, Node* poly)
{
    printf("%s\n", msg);
    size_t n;
    printf("Number of terms: "); scanf("%zu", &n);
    printf("Coefficients, Powers:\n");
    /* These are variables that might used used in the loop. */
    Node* x; Node* q = poly;
    int c, p;
    for (size_t i = 0; i < n; ++i) {
        scanf("%d %d", &c, &p);
        x = term(c, p);
        if (q == NULL) poly = (q = x); else { q->next = x; q = q->next; };
    }
    return poly;
}

void print_polynomial(char* msg, Node* poly)
{
    printf("%s", msg);
    Node* p = poly;
    while (p != NULL) {
        if (p->c == 0) continue;
        else if (p->c == 1 || p->c == -1) {
            if (p->p == 0) printf("1");
        } else printf("%d", p == poly ? p->c : abs(p->c));

        if (p->p == 0);
        else if (p->p == 1) printf("x");
        else printf("x^%d", p->p);

        if (p->next != NULL) {
            if (p->next->c < 0) printf(" - ");
            else if (p->next->c > 0) printf(" + ");
        }
        p = p->next;
    }
    puts("");
}

int main()
{
    poly_1 = read_polynomial("Polynomial 1: ", poly_1);
    poly_2 = read_polynomial("\nPolynomial 2: ", poly_2);
    print_polynomial("\nPolynomial 1: ", poly_1);
    print_polynomial("Polynomial 2: ", poly_2);
    poly_0 = add_polynomials(poly_1, poly_2, poly_0);
    print_polynomial("\nResult: ", poly_0);

    return 0;
}
