#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define     DISKSTART       0
#define     DISKEND         200

typedef     enum { FCFS, SCAN, CSCAN }      schedule_type;

size_t dist(size_t x, size_t y)
{
    if (x > y) return (x - y);
    else return (y - x);
}

size_t linear_search(size_t *a, size_t n, size_t key)
{
    if (n < 1) return n;
    for (size_t i = 0; i < n; ++i)
        if (a[i] == key)
            return i;
    return n;
}

int compar(const void *a, const void *b)
{
    size_t *x = (size_t*) a, *y = (size_t*) b;
    if (*x < *y) return -1;
    else if (*x > *y) return 1;
    else return 0;
}

void schedule(size_t *diskqueue, size_t n, size_t head, schedule_type st)
{
    size_t sq[2 * n];           /*  The disk queue after scheduling                 */
    size_t tot_hdmov = 0;       /*  The total head movement                         */
    size_t i;                   /*  The current index of the disk queue             */
    size_t j = 0;               /*  The current index of the scheduling queue       */
    size_t h;                   /*  The initial position of head for SCAN and CSCAN */
    size_t dq[n + 1];           /*  A copy of the disk queue for in-place sorting   */

    dq[0] = head;
    for (size_t i = 0; i < n; ++i)
        dq[i + 1] = diskqueue[i];

    switch (st) {
        case (FCFS):
            for (i = 0; i < n + 1; ++i)
                sq[j++] = dq[i];
            break;

        case (SCAN):
        case (CSCAN):
            qsort(dq, n + 1, sizeof (size_t), compar);

            h = linear_search(dq, n + 1, head);
            for (i = h; i < n + 1; ++i)
                sq[j++] = dq[i];
            sq[j++] = DISKEND;
            
            if (st == SCAN) {
                for (i = h - 1; i < n; --i)
                    sq[j++] = dq[i];
            } else {
                sq[j++] = DISKSTART;
                for (i = 0; i < h; ++i)
                    sq[j++] = dq[i];
            }
            break;
    }

    printf("Schedule (%zu):", j);
    for (size_t k = 0; k < j - 1; ++k) {
        printf("%4zu", sq[k]);
        tot_hdmov += dist(sq[k], sq[k + 1]);
    }
    printf("%4zu\n", sq[j - 1]);
    printf("Total head movement: %4zu\n", tot_hdmov);
}

int main()
{
    size_t n;
    printf("No. of requests: ");
    scanf("%zu", &n);

    size_t diskqueue[n];
    printf("\nRequest Queue (%d-%d) >>>\n", DISKSTART, DISKEND);
    for (size_t i = 0; i < n; ++i)
        scanf("%zu", &diskqueue[i]);

    size_t head;
    printf("\nHead at: ");
    scanf("%zu", &head);

    puts("\nFCFS");
    schedule(diskqueue, n, head, FCFS);
    puts("\nSCAN");
    schedule(diskqueue, n, head, SCAN);
    puts("\nC-SCAN");
    schedule(diskqueue, n, head, CSCAN);

    return 0;
}
