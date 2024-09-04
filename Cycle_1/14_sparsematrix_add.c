#include <stdio.h>
#include <stdlib.h>
#define SM_COL 3

int main ();
int** read_sm (char*, int(*)[SM_COL]);
int** add_sm (int(*)[SM_COL], int(*)[SM_COL]);
int occur_cmp (size_t, size_t, size_t, size_t);
void print_sm (char*, int(*)[SM_COL]);

int main()
{
    size_t m, n;
    printf("Order of matrices: "); scanf("%zu %zu", &m, &n);

    int (*sm1)[SM_COL] = malloc(sizeof (int[1][SM_COL]));
    sm1[0][0] = m; sm1[0][1] = n;
    sm1 = (int(*)[SM_COL]) read_sm("\nMatrix #1:", sm1);

    int (*sm2)[SM_COL] = malloc(sizeof (int[1][SM_COL]));
    sm2[0][0] = m; sm2[0][1] = n;
    sm2 = (int(*)[SM_COL]) read_sm("\nMatrix #2:", sm2);

    print_sm("\nSM #1:", sm1);
    print_sm("\nSM #2:", sm2);

    int (*sm3)[SM_COL] = (int(*)[SM_COL]) add_sm(sm1, sm2);
    print_sm("\nSum: ", sm3);

    free(sm1); free(sm2); free(sm3);
    return 0;
}

int** read_sm(char *msg, int (*sm)[SM_COL])
{
    printf("%s\n", msg);
    size_t m = sm[0][0];
    size_t n = sm[0][1];
    size_t k = 1;
    int v;
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            scanf("%d", &v);
            if (v != 0) {
                sm = realloc(sm, sizeof (int[k + 1][SM_COL]));
                sm[k][0] = i;
                sm[k][1] = j;
                sm[k++][2] = v; /* This makes k one greater when the loop exits. */
            }
        }
    }
    sm[0][2] = k - 1; /* k is one greater when the loop exits. */
    return (int**) sm;
}

int** add_sm(int (*sm1)[SM_COL], int (*sm2)[SM_COL])
{
    size_t k1 = sm1[0][2], k2 = sm2[0][2];
    int (*sm3)[SM_COL] = malloc(sizeof (int[1][SM_COL]));
    sm3[0][0] = sm1[0][0]; sm3[0][1] = sm1[0][1];

    size_t i = 1, j = 1, k = 1;
    while (i <= k1 && j <= k2) {
        sm3 = realloc(sm3, sizeof (int[k + 1][SM_COL]));
        int occur = occur_cmp(sm1[i][0], sm1[i][1], sm2[j][0], sm2[j][1]);
        if (occur == 0) {
            sm3[k][0] = sm1[i][0]; sm3[k][1] = sm1[i][1];
            sm3[k++][2] = sm1[i++][2] + sm2[j++][2];
        } else if (occur < 0) {
            sm3[k][0] = sm1[i][0]; sm3[k][1] = sm1[i][1];
            sm3[k++][2] = sm1[i++][2];
        } else {
            sm3[k][0] = sm2[j][0]; sm3[k][1] = sm2[j][1];
            sm3[k++][2] = sm2[j++][2];
        }
    }
    while (i <= k1) {
        sm3 = realloc(sm3, sizeof (int[k + 1][SM_COL]));
        sm3[k][0] = sm1[i][0]; sm3[k][1] = sm1[i][1];
        sm3[k++][2] = sm1[i++][2];
    }
    while (j <= k2) {
        sm3 = realloc(sm3, sizeof (int[k + 1][SM_COL]));
        sm3[k][0] = sm2[j][0]; sm3[k][1] = sm2[j][1];
        sm3[k++][2] = sm2[j++][2];
    }
    sm3[0][2] = k - 1;
    return (int**) sm3;
}

int occur_cmp(size_t m1, size_t n1, size_t m2, size_t n2)
{
    if (m1 == m2) return n1 - n2;
    else return m1 - m2;
}

void print_sm(char *msg, int (*sm)[SM_COL])
{
    printf("%s\n", msg);
    size_t elemc = sm[0][2];
    for (size_t k = 0; k <= elemc; ++k)
        printf("[%3d %3d %3d]\n", sm[k][0], sm[k][1], sm[k][2]);
}
