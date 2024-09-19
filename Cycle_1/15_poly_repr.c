#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Type declarations */
typedef struct Term {
    long c; /* for the coefficient. */
    long e; /* for the exponent. */
} Term;

typedef struct Polynomial {
    size_t n; /* for the number of terms. */
    Term* p; /* for the polynomial itself. */
} Polynomial;

/* Function declarations */
int main ();
void read_polynomial (Polynomial*);
void print_polynomial (char*, Polynomial);

int main()
{
    Polynomial f;
    read_polynomial(&f);
    print_polynomial("Result: ", f);
    free(f.p);
}

void read_polynomial(Polynomial* f) {
    printf("Number of terms: "); scanf("%zu", &f->n);
    f->p = malloc(f->n * sizeof f->p);
    printf("Coefficients and degrees: \n");
    for (size_t i = 0; i < f->n; ++i) 
        scanf("%ld %ld", &f->p[i].c, &f->p[i].e);
}

void print_polynomial(char* msg, Polynomial f) {
    printf("%s", msg);
    bool is_neg;
    for (size_t i = 0; i < f.n; ++i) {
        is_neg = false;
        if (i != 0) {
            if (f.p[i].c < 0) {
                printf(" - ");
                is_neg = true;
            } else printf(" + ");
        }

        if (f.p[i].c == 0) continue;
        else if (f.p[i].c == 1);
        else printf("%ld", is_neg ? -f.p[i].c : f.p[i].c);

        if (f.p[i].e == 0);
        else if (f.p[i].e == 1) printf("x");
        else printf("x^%ld", f.p[i].e);
    } puts("");
}
