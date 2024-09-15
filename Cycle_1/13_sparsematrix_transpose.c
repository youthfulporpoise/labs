#include <stdio.h>
#include <stdlib.h>
#define SM_COL 3

int main ();
void transpose_sm(long(*)[SM_COL]);
long** read_sm (char*, long(*)[SM_COL]);
void print_sm (char*, long(*)[SM_COL]);

long __tmp__;
#define SWAP(a, b) { __tmp__ = (a); (a) = (b); (b) = __tmp__; }

int main()
{
    size_t m, n;
    printf("Order of matrix: "); scanf("%zu %zu", &m, &n);

    long (*sm)[SM_COL] = malloc(sizeof (long[1][SM_COL]));
    sm[0][0] = m; sm[0][1] = n;
    sm = (long(*)[SM_COL]) read_sm("\nMatrix:", sm);

    print_sm("\nSM Representation:", sm);
    transpose_sm(sm);
    print_sm("\nResult:", sm);
    free(sm);
    return 0;
}

void transpose_sm(long(*sm)[SM_COL]) {
    size_t k = sm[0][2];
    for (size_t i = 0; i <= k; ++i) SWAP(sm[i][0], sm[i][1]);
}

long** read_sm(char *msg, long (*sm)[SM_COL])
{
    printf("%s\n", msg);
    size_t m = sm[0][0];
    size_t n = sm[0][1];
    size_t k = 1;
    long v;
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            scanf("%ld", &v);
            if (v != 0) {
                sm = realloc(sm, sizeof (int[k + 1][SM_COL]));
                sm[k][0] = i;
                sm[k][1] = j;
                sm[k++][2] = v; /* This makes k one greater when the loop exits. */
            }
        }
    }
    sm[0][2] = k - 1; /* k is one greater when the loop exits. */
    return (long**) sm;
}

void print_sm(char *msg, long (*sm)[SM_COL])
{
    printf("%s\n", msg);
    size_t elemc = sm[0][2];
    for (size_t k = 0; k <= elemc; ++k)
        printf("[%3ld %3ld %3ld]\n", sm[k][0], sm[k][1], sm[k][2]);
}
