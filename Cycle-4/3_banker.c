/* QUESTION 3.
 * Write a C program to simulate Banker’s algorithm for deadlock avoidance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void)
{
    /* The resource count and process count resp. */
    size_t resc, prc;
    printf("Number of resources: ");
    scanf("%zu", &resc);
    printf("Number of processes: ");
    scanf("%zu", &prc);

    unsigned allocated[prc][resc];
    puts("\nALLOCATION:");
    for (size_t i = 0; i < prc; ++i)
        for (size_t j = 0; j < resc; ++j)
            scanf("%u", &allocated[i][j]);

    unsigned maximum[prc][resc];
    puts("\nMAXIMUM:");
    for (size_t i = 0; i < prc; ++i)
        for (size_t j = 0; j < resc; ++j)
            scanf("%u", &maximum[i][j]);

    unsigned available[resc];
    puts("\nAVAILABLE:");
    for (size_t i = 0; i < resc; ++i)
        scanf("%u", &available[resc]);

    unsigned need[prc][resc];
    for (size_t i = 0; i < prc; ++i)
        for (size_t j = 0; j < resc; ++j)
            need[i][j] = maximum[i][j] - allocated[i][j];

    puts("\nNEED");
    for (size_t i = 0; i < prc; ++i) {
        for (size_t j = 0; j < resc; ++j)
            printf("%u ", need[i][j]);
        printf("\n");
    } printf("\n");


    /* We simulate Banker’s algorithm to determine the safe state. */
    bool safe;            /* Is a safe state achievable? (false is a placeholder) */
    bool none;            /* Are none of the processes terminable? */
    size_t safeseq[prc];  /* If so, what is the safe sequence? */
    size_t sf = 0;        /* The safe sequence index */
    bool finish[prc];     /* Which processes have succesfully terminated? */

    size_t p;  /* ID of the requesting process in queue */
    bool suff; /* Are resources sufficient for the process? */
    while (true) {
        for (p = 0; p < prc; ++p) {
            /* The process has already terminted, skip. */
            if (finish[p])
                continue;

            /* Compare and determine whether the request can be granted. */
            suff = true;
            for (size_t i = 0; i < resc; ++i) {
                if (need[p][i] > available[i]) {
                    suff = false;
                    finish[p] = false;
                    break;
                }
            }

            /* If the request can be granted, terminate it and release the
             * resources. */
            if (suff) {
                safeseq[sf++] = p;
                for (size_t i = 0; i < resc; ++i) {
                    available[i] += allocated[p][i];
                    allocated[p][i] = 0;
                }
                finish[p] = true;
            }
        }
        /* Determine whether the requests are completely, partially, or not
         * satisfiable. */
        safe = true;
        none = false;
        for (size_t i = 0; i < prc; ++i) {
            safe &= finish[i];
            none |= finish[i];
        }
        if (safe) break;
        else if (none) continue;
    }

    if (safe) {
        puts("A safe state is achievable.");
        printf("Safe sequence: ");
        for (size_t i = 0; i < prc; ++i)
            printf("P%-2zu ", safeseq[i]);
        printf("\n");
    } else {
        puts("A safe state is not achievable.");
    }

    return 0;
}
