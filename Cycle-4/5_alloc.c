/* QUESTION 5.
 * Write a C program to implement the memory allocation methods for fixed
 * partitions:
 *   (a) first fit;
 *   (b) worst fit;
 *   (c) best fit.
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void sort_asc(int *a, size_t n)
{
    size_t i, j;
    int x;
    for (i = 1; i < n; ++i) {
        x = a[i];
        j = i;
        while (j > 0 && x < a[j - 1]) {
            a[j] = a[j - 1];
            --j;
        } a[j] = x;
    }
}

void sort_dsc(int *a, size_t n)
{
    size_t i, j;
    int x;
    for (i = 1; i < n; ++i) {
        x = a[i];
        j = i;
        while (j > 0 && x > a[j - 1]) {
            a[j] = a[j - 1];
            --j;
        } a[j] = x;
    }
}

void first_fit(int *req, size_t n, int *part, size_t m)
{
    bool grant;
    int prev_size;

    printf("\nFIRST FIT\n");
    printf("\n%12s %12s %12s %12s\n", "REQUEST", "PARTITION", "GRANT", "REMAINING");
    size_t i, j;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            if (part[j] >= req[i]) grant = true;
            else grant = false;

            prev_size = part[j];
            if (grant) {
                part[j] -= req[i];
                break;
            } else continue;
        }
        printf("%12d %12d %12s %12d\n", req[i], prev_size, grant ? "Yes" : "No", j < m ? part[j] : prev_size);
    }
}

void best_fit(int *req, size_t n, int *part, size_t m)
{
    sort_asc(part, m);

    bool grant;
    int prev_size;

    printf("\nBEST FIT\n");
    printf("\n%12s %12s %12s %12s\n", "REQUEST", "PARTITION", "GRANT", "REMAINING");
    size_t i, j;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            if (part[j] >= req[i]) grant = true;
            else grant = false;

            prev_size = part[j];
            if (grant) {
                part[j] -= req[i];
                break;
            } else continue;
        }
        printf("%12d %12d %12s %12d\n", req[i], prev_size, grant ? "Yes" : "No", j < m ? part[j] : prev_size);
    }
}

void worst_fit(int *req, size_t n, int *part, size_t m)
{
    sort_dsc(part, m);

    bool grant;
    int prev_size;

    printf("\nWORST FIT\n");
    printf("\n%12s %12s %12s %12s\n", "REQUEST", "PARTITION", "GRANT", "REMAINING");
    size_t i, j;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            if (part[j] >= req[i]) grant = true;
            else grant = false;

            prev_size = part[j];
            if (grant) {
                part[j] -= req[i];
                break;
            } else continue;
        }
        printf("%12d %12d %12s %12d\n", req[i], prev_size, grant ? "Yes" : "No", j < m ? part[j] : prev_size);
    }
}


int main(void)
{
    size_t m;
    printf("Number of partitions: ");
    scanf("%zu", &m);

    int part[m];
    printf("Partitions: ");
    for (size_t i = 0; i < m; ++i)
        scanf("%d", &part[i]);

    size_t n;
    printf("Number of requests: ");
    scanf("%zu", &n);

    int req[n];
    printf("Requests: ");
    for (size_t i = 0; i < n; ++i)
        scanf("%d", &req[i]);

    int part_1[m];
    memcpy(part_1, part, sizeof (int) * m);
    first_fit(req, n, part_1, m);

    int part_2[m];
    memcpy(part_2, part, sizeof (int) * m);
    best_fit(req, n, part_2, m);

    int part_3[m];
    memcpy(part_3, part, sizeof (int) * m);
    worst_fit(req, n, part_3, m);

    return 0;
}
