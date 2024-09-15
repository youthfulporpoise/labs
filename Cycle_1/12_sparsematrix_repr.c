#include <stdio.h>
#define SM_COL 3
#define SM_ROW 100

int main ();
void read_sm (char*, int**);
void print_sm (char*, int**);

int main()
{
    size_t m, n;
    printf("Row size: "); scanf("%zu", &m);
    printf("Column size: "); scanf("%zu", &n);

    int sm[SM_COL][SM_ROW];
    sm[0][0] = m; sm[0][1] = n;
    printf("%d %d %d\n", sm[0][0], sm[0][1], sm[0][2]);

    read_sm("Matrix: ", sm);
    print_sm("Sparse matrix representation: ", sm);

    return 0;
}

void read_sm(char *msg, int **sm)
{
    /* We assume that sm has non-zero size and that
     * sm contains the row and column size specified
     * of the matrix. */
    printf("%s\n", msg);
    size_t m = sm[0][0];
    size_t n = sm[0][1];
    size_t k = 1;
    puts("Checkpoint 1");
    int v;
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            scanf("%d", &v);
            if (v != 0) {
                sm[k][0] = i;
                sm[k][1] = j;
                sm[k++][2] = v;
            }
        }
    }
    sm[0][2] = k;
}

void print_sm(char *msg, int **sm)
{
    printf("%s\n", msg);
    size_t elemc = sm[0][2];
    for (size_t k = 0; k <= elemc; ++k)
        printf("[%3d %3d %3d]\n", sm[k][0], sm[k][1], sm[k][2]);
}
