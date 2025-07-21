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
    puts("\nALLOCATION >>>");
    for (size_t i = 0; i < prc; ++i)
        for (size_t j = 0; j < resc; ++j)
            scanf("%u", &allocated[i][j]);

    unsigned maximum[prc][resc];
    puts("\nMAXIMUM >>>");
    for (size_t i = 0; i < prc; ++i)
        for (size_t j = 0; j < resc; ++j)
            scanf("%u", &maximum[i][j]);

    unsigned available[resc];
    puts("\nAVAILABLE >>>");
    for (size_t i = 0; i < resc; ++i)
        scanf("%u", &available[i]);

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
    size_t safeseq[prc];  /* If so, what is the safe sequence? */
    size_t sf = 0;        /* The safe sequence index */
    bool finish[prc];     /* Which processes have succesfully terminated? */

    for (size_t i = 0; i < prc; ++i)
        finish[i] = false;

    bool suff = false;      /* Is the available resources sufficient? */
    size_t p = 0;
    while (p < prc) {
        /* If already terminated, skip. */
        if (finish[p]) {
            p++;
            continue;
        }

        /* If the request can be granted, write safe sequence and terminate the
         * process. */
        suff = true;
        for (size_t i = 0; i < resc; ++i) {
            if (need[p][i] > maximum[p][i]) {
                suff = false;
                break;
            } else if (need[p][i] > available[i]) {
                suff = false;
                break;
            }
        }
        if (suff) {
            safeseq[sf++] = p;
            finish[p] = true;
        } else {
            p++;
            continue;
        }
        
        /* Release the acquired resources.  Enumerate the processes from the
         * beginning afterwards. */
        for (size_t i = 0; i < resc; ++i) {
            available[i] += allocated[p][i];
            allocated[p][i] = 0;
        }
        p = 0;
        continue;
    }

    safe = true;
    for (size_t i = 0; i < prc; ++i)
        safe &= finish[i];

    if (safe) {
        puts("A safe state is achievable.");
        printf("Safe sequence: ");
        for (size_t i = 0; i < prc; ++i)
            printf("P%-2zu ", safeseq[i]);
        puts("");
    } else {
        puts("A safe state is not achievable.");
    }

    return 0;
}
