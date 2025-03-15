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


size_t min(ssize_t *a, size_t n)
{
    size_t m = 0;
    for (size_t i = 0; i < n; ++i)
        if (a[i] < a[m])
            m = i;
    return m;
}

void lfu_replace(size_t *refstr, size_t n, size_t frmc)
{
    ssize_t pgfrm[2][frmc];

    for (size_t i = 0; i < frmc; ++i) {
        pgfrm[0][i] = -1;
        pgfrm[1][i] = -1;
    }

    puts("LEAST-FREQUENTLY USED REPLACEMENT");
    size_t z; /* the index of the least frequently used */
    for (size_t i = 0; i < n; ++i) {
        z = loaded(pgfrm[0], frmc, refstr[i]);
        if (z == frmc) {
            z = min(pgfrm[1], frmc);
            // printf("MIN: %zu\n", z);
            pgfrm[0][z] = refstr[i];
            pgfrm[1][z] = 1;
        } else pgfrm[1][z]++;

        printf("%3zu: ", refstr[i]);
        for (size_t j = 0; j < frmc && pgfrm[0][j] >= 0; ++j)
            printf("%3zu ", pgfrm[0][j]);
        puts("");
    }
    puts("");
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
