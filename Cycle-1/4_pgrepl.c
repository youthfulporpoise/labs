#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define     PRINT_PGFRM(refn, pgfrm, size)  \
    printf("%-4ld ->", (refn));             \
    for (size_t i = 0; i < (size); ++i)     \
        if ((pgfrm)[i] >= 0)                \
            printf(" %4ld", (pgfrm)[i]);    \
    printf("\n");

typedef     enum { FIFO, LRU, LFU }     pgrepl_type;

size_t is_loaded(ssize_t *pgfrm, size_t size, ssize_t frm)
{
    for (size_t i = 0; i < size; ++i)
        if (pgfrm[i] == frm)
            return i;
    return size;
}

size_t least_frequent(ssize_t *pgfrm, size_t n, ssize_t *refstr, size_t m)
{
    size_t *freq = calloc(n, sizeof (size_t));
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            if (refstr[j] == pgfrm[i])
                freq[i]++;
    size_t min = 0;
    for (size_t i = 0; i < n; ++i)
        if (freq[i] < freq[min])
            min = i;
    return min;
}

void page_replace(ssize_t *refstr, size_t size, size_t frmc, pgrepl_type pgrt)
{
    ssize_t pgfrm[frmc];        /*  The pageframes array                        */
    size_t w = 0;               /*  The pageframes array index                  */
    size_t z;                   /*  The index of a loaded pageframe             */
    size_t v;                   /*  The start index for array shifting in LRU   */
    size_t f;                   /*  The least-frequent pageframe in LFU         */
    for (size_t i = 0; i < frmc; ++i)
        pgfrm[i] = -1;

    switch (pgrt) {
        case (FIFO):
            for (size_t i = 0; i < size; ++i) {
                if (is_loaded(pgfrm, frmc, refstr[i]) == frmc) {
                    pgfrm[w] = refstr[i];
                    w = (w + 1) % frmc;
                }
                PRINT_PGFRM(refstr[i], pgfrm, frmc);
            }
            break;

        case (LRU):
            for (size_t i = 0; i < size; ++i) {
                z = is_loaded(pgfrm, frmc, refstr[i]);
                if (z == frmc)  v = 0;
                else            v = z;
                while (v < frmc) {
                    pgfrm[v] = pgfrm[v + 1];
                    v++;
                } pgfrm[frmc - 1] = refstr[i];
                PRINT_PGFRM(refstr[i], pgfrm, frmc);
            }
            break;

        case (LFU):
            for (size_t i = 0; i < size; ++i) {
                z = is_loaded(pgfrm, frmc, refstr[i]);
                if (z == frmc) {
                    f = least_frequent(pgfrm, frmc, refstr, i + 1);
                    pgfrm[f] = refstr[i];
                }
                PRINT_PGFRM(refstr[i], pgfrm, frmc);
            }
    }
}

int main(int argc, char **argv)
{
    size_t frmc, reqc;
    printf("Number of frames: ");
    scanf("%zu", &frmc);
    printf("Number of requents: ");
    scanf("%zu", &reqc);

    ssize_t refstr[reqc];
    printf("REFERENCE STRING: ");
    for (size_t i = 0; i < reqc; ++i)
        scanf("%ld", &refstr[i]);

    puts("\nFIFO");
    page_replace(refstr, reqc, frmc, FIFO);
    puts("\nLRU");
    page_replace(refstr, reqc, frmc, LRU);
    puts("\nLFU");
    page_replace(refstr, reqc, frmc, LFU);

    return 0;
}
