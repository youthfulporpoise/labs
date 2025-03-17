/* QUESTION 4.
 * Write a C program to implement to following page replacement algorithms:
 *   a. first-in first-out;
 *   b. least-recently used;
 *   c. least-frequently used.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


size_t loaded(ssize_t *pgfrm, size_t n, size_t x)
{
    size_t i;
    for (i = 0; i < n; ++i)
        if (pgfrm[i] == x)
            return i;
    return i;
}


void fifo_replace(size_t *refstr, size_t n, size_t frmc)
{
    ssize_t pgfrm[frmc];
    size_t w = 0;  /* i is the index of the oldest frame */

    /* Initialize the frames to load nothing */
    for (size_t i = 0; i < frmc; ++i)
        pgfrm[i] = -1;

    /* Read through the reference string. */
    puts("FIRST-IN FIRST-OUT REPLACEMENT");
    for (size_t i = 0; i < n; ++i) {
        if (loaded(pgfrm, frmc, refstr[i]) >= frmc) {
            pgfrm[w] = refstr[i];
            w = (w + 1) % frmc;
        }
        printf("%3zu: ", refstr[i]);
        for (size_t j = 0; j < frmc && pgfrm[j] >= 0; ++j)
            printf("%3zu ", pgfrm[j]);
        puts("");
    }
    puts("");
}


void lru_replace(size_t *refstr, size_t n, size_t frmc)
{
    /* pgfrm is a stack. */
    ssize_t pgfrm[frmc];
    size_t w = 0;

    for (size_t i = 0; i < frmc; ++i)
        pgfrm[i] = -1;

    puts("LEAST-RECENTLY USED REPLACEMENT");
    size_t z; /* the index of an already loaded page */
    for (size_t i = 0; i < n; ++i) {
        if (w < frmc)
            pgfrm[w++] = refstr[i];
        else {
            z = loaded(pgfrm, w, refstr[i]);
            size_t v;
            if (z == frmc)
                v = 0;
            else
                v = z;
            while (v < w) {
                pgfrm[v] = pgfrm[v + 1];
                v++;
            } pgfrm[w - 1] = refstr[i];
        }
        printf("%3zu: ", refstr[i]);
        for (size_t j = 0; j < frmc && pgfrm[j] >= 0; ++j)
            printf("%3zu ", pgfrm[j]);
        puts("");
    }
    puts("");
}


/* Find amongst the values in the array the one that has the least occurence in
 * refstr.  Return the index of the least frequent. */
size_t min(ssize_t *a, size_t n, size_t *refstr, size_t m)
{
    size_t *b = calloc(n, sizeof (size_t));
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            if (refstr[j] == a[i])
                b[i]++;

    size_t min = 0;
    for (size_t i = 0; i < n; ++i)
        if (b[i] < b[min])
            min = i;
    return min;
}

void lfu_replace(size_t *refstr, size_t n, size_t frmc)
{
    ssize_t pgfrm[frmc];
    for (size_t i = 0; i < frmc; ++i)
        pgfrm[i] = -1;

    puts("LEAST-FREQUENTLY USED REPLACEMENT");
    /* The loaded flag and least-frequent page resp. */
    size_t z, f;
    for (size_t i = 0; i < n; ++i) {
        z = loaded(pgfrm, frmc, refstr[i]);
        if (z == frmc) {
            f = min(pgfrm, frmc, refstr, i + 1);
            pgfrm[f] = refstr[i];
        }

        printf("%3zu: ", refstr[i]);
        for (size_t j = 0; j < frmc && pgfrm[j] >= 0; ++j)
            printf("%3zu ", pgfrm[j]);
        puts("");
    }
}


int main(void)
{
    size_t frmc;
    printf("Number of frames: ");
    scanf("%zu", &frmc);

    size_t reqc;
    printf("Number of requests: ");
    scanf("%zu", &reqc);

    size_t refstr[reqc];
    printf("Reference string: ");
    for (size_t i = 0; i < reqc; ++i)
        scanf("%zu", &refstr[i]);

    puts("\nREFERENCE STRING");
    for (size_t i = 0; i < reqc; ++i)
        printf("%zu ", refstr[i]);
    puts("\n");

    fifo_replace(refstr, reqc, frmc);
    lru_replace(refstr, reqc, frmc);
    lfu_replace(refstr, reqc, frmc);

    return 0;
}
