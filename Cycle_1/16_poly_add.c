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
/* Any modifications to p in any local scope will reflect in any scope since its
 * type is Term*.  Therefore returning a local Polynomial will return a copy
 * that has same contents as the local copy.  The array p is itself not copied,
 * but it pointer. Vide the signature of add_polynomial. */

/* Function declarations */
int main ();
Polynomial add_polynomial(Polynomial, Polynomial);
void read_polynomial (Polynomial*);
void print_polynomial (char*, Polynomial);

int main()
{
    Polynomial f1;
    read_polynomial(&f1);

    Polynomial f2;
    read_polynomial(&f2);

    Polynomial f = add_polynomial(f1, f2);
    
    print_polynomial("\nPolynomial 1: ", f1);
    print_polynomial("Polynomial 2: ", f2);
    print_polynomial("Result: ", f);

    free(f1.p); free(f2.p); free(f.p);
    return 0;
}

Polynomial add_polynomial(Polynomial f, Polynomial g) {
    Polynomial h;
    h.n = f.n + g.n;
    h.p = malloc(h.n * sizeof (Term));
    size_t i = 0, j = 0, k = 0;
    /* The polynomial is assumed to be sorted in descending 
     * order of powers. */
    while (i < f.n && j < g.n) {
        if (f.p[i].e == g.p[j].e) {
            h.p[k].e = f.p[i].e;
            h.p[k++].c = f.p[i++].c + g.p[j++].c;
        } else if (f.p[i].e > g.p[j].e) {
            h.p[k].e = f.p[i].e;
            h.p[k++].c = f.p[i++].c;
        } else {
            h.p[k].e = g.p[j].e;
            h.p[k++].c = g.p[j++].c;
        }
    } while (i < f.n) {
        h.p[k].e = f.p[i].e;
        h.p[k++].c = f.p[i++].c;
    } while (j < g.n) {
        h.p[k].e = g.p[j].e;
        h.p[k++].c = g.p[j++].c;
    } h.n = k;
    h.p = realloc(h.p, h.n * sizeof (Term));
    return h;
}

void read_polynomial(Polynomial* f) {
    printf("\nNumber of terms: "); scanf("%zu", &f->n);
    f->p = malloc(f->n * sizeof (Term));
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
