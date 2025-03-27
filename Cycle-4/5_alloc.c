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

void first_fit(char *msg, int *req, size_t n, int *part, size_t m)
{
    bool grant;
    int prev_size;

    printf("\n%s\n", msg);
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

void best_fit(char *msg, int *req, size_t n, int *part, size_t m)
{
    for (size_t i = 0; i < m; ++i)
        printf("%d ", part[i]);
    puts("");
    sort_asc(part, m);
    for (size_t i = 0; i < m; ++i)
        printf("%d ", part[i]);
    puts("");
    first_fit(msg, req, n, part, m);
}

void worst_fit(char *msg, int *req, size_t n, int *part, size_t m)
{
    for (size_t i = 0; i < m; ++i)
        printf("%d ", part[i]);
    puts("");
    sort_dsc(part, m);
    for (size_t i = 0; i < m; ++i)
        printf("%d ", part[i]);
    puts("");
    first_fit(msg, req, n, part, m);
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

    int part_copy_1[m], part_copy_2[m];
    memcpy(part_copy_1, part, sizeof (int) * m);
    memcpy(part_copy_2, part, sizeof (int) * m);

    first_fit("FIRST FIT", req, n, part, m);
    best_fit("BEST FIT", req, n, part_copy_1, m);
    worst_fit("WORST FIT", req, n, part_copy_2, m);

    return 0;
}
