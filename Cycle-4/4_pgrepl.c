/* QUESTION 4.
 * Write a C program to implement to following page replacement algorithms:
 *   a. first-in first-out;
 *   b. least-recently used;
 *   c. least-frequently used.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


bool loaded(ssize_t *pgfrm, size_t n, size_t x)
{
    for (size_t i = 0; i < n; ++i)
        if (pgfrm[i] == x)
            return true;
    return false;
}


void fifo_replace(size_t *refstr, size_t n, size_t frmc)
{
    ssize_t pgfrm[frmc];
    size_t w = 0;  /* i is the index of the oldest frame */

    /* Initialize the frames to load the first three pages */
    for (size_t i = 0; i < frmc; ++i)
        pgfrm[i] = -1;

    /* Read through the reference string. */
    puts("FIRST-IN FIRST-OUT REPLACEMENT");
    for (size_t i = 0; i < n; ++i) {
        if (!loaded(pgfrm, frmc, refstr[i])) {
            pgfrm[w] = refstr[i];
            w = (w + 1) % frmc;
        }
        printf("%3zu: ", refstr[i]);
        for (size_t j = 0; j < frmc && pgfrm[j] >= 0; ++j) {
            printf("%3zu ", pgfrm[j]);
        } puts("");
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
}
