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
void read_polynomial (Polynomial*);
Polynomial mult_polynomial (Polynomial, Polynomial);
void print_polynomial (char*, Polynomial);

int main()
{
    Polynomial f1;
    read_polynomial(&f1);

    Polynomial f2;
    read_polynomial(&f2);

    Polynomial f = mult_polynomial(f1, f2);
    
    print_polynomial("\nPolynomial 1: ", f1);
    print_polynomial("Polynomial 2: ", f2);
    print_polynomial("Result: ", f);

    free(f1.p); free(f2.p); free(f.p);
    return 0;
}

Polynomial mult_polynomial(Polynomial f, Polynomial g) {
    Polynomial h;
    h.n = f.p[0].e * f.p[0].e;
    h.p = calloc(h.n, sizeof (Term));

    size_t z = 0;
    bool degree_exists;
    for (long k = f.p[0].e + f.p[0].e; k >= 0; k--) {
        degree_exists = false;
        for (size_t i = 0; i < f.n; i++) {
            for (size_t j = 0; j < g.n; ++j) {
                if (f.p[i].e + g.p[j].e == k) {
                    h.p[z].e = k;
                    h.p[z].c += f.p[i].c * g.p[j].c;
                    degree_exists = true;
                }
            }
        }
        if (degree_exists) z++;
    }

    h.n = z;
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
        else if (f.p[i].c == 1 && f.p[i].e != 0);
        else printf("%ld", is_neg ? -f.p[i].c : f.p[i].c);

        if (f.p[i].e == 0);
        else if (f.p[i].e == 1) printf("x");
        else printf("x^%ld", f.p[i].e);
    } puts("");
}
