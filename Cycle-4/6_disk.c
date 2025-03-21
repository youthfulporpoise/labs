/* QUESTION 6.
 * Write a C program to simulate disk scheduling algorithms.
 *   (a) FCFS
 *   (b) SCAN
 *   (c) C-SCAN
 */

#include <stdio.h>
#include <stdlib.h>

#define DISKSTART 0
#define DISKEND 200

/* O(n^2)  O(n^2)  O(n)  Stable */
void sort(int *a, size_t n)
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

/* O(log n)  O(log n)  O(log n) */
size_t find(int *a, size_t n, int key)
{
    size_t l = 0, r = n, z;
    while (l < r) {
        z = (l + r) / 2;
        if (key > a[z])
            l = z;
        else if (key < a[z])
            r = z + 1;
        else return z;
    } return n;
}

/* O(n)  O(n)  O(n) */
size_t search(int *a, size_t n, int key)
{
    for (size_t i = 0; i < n; ++i)
        if (a[i] == key)
            return i;
    return n;
}

void fcfs_schedule(int *diskqueue, size_t n, int head)
{
    int hdmov = 0, curr, prev;
    size_t i = 0;
    curr = prev = diskqueue[0];

    printf("\nFCFS SCHEDULING\n");
    while (i < n) {
        printf("%2d ", curr = diskqueue[i++]);
        hdmov += abs(curr - prev);
        prev = curr;
    } puts("");

    printf("Total head movment is %d.\n", hdmov);
}

void scan_schedule(int *diskqueue, size_t n, int head)
{
    int hdmov = 0, prev, curr;
    size_t h, i;

    sort(diskqueue, n);
    h = i = search(diskqueue, n, head);
    curr = prev = diskqueue[h];

    printf("\nSCAN SCHEDULING\n");
    while (i < n) {
        printf("%2d ", curr = diskqueue[i++]);
        hdmov += abs(curr - prev);
        prev = curr;
    }

    i = h;
    curr = DISKEND;
    hdmov += abs(curr - prev);
    prev = curr;
    printf("%2d ", curr);

    while (i > 0) {
        printf("%2u ", curr = diskqueue[--i]);
        hdmov += abs(curr - prev);
        prev = curr;
    } puts("");

    printf("Total head movement is %d.\n", hdmov);
}

void cscan_schedule(int *diskqueue, size_t n, int head)
{
    int hdmov = 0, prev, curr;
    size_t h, i;

    sort(diskqueue, n);
    h = i = search(diskqueue, n, head);
    curr = prev = diskqueue[h];

    printf("\nSCAN SCHEDULING\n");
    while (i < n) {
        printf("%2d ", curr = diskqueue[i++]);
        hdmov += abs(curr - prev);
        prev = curr;
    }

    i = 0;
    curr = DISKEND;
    printf("%2d", curr);
    hdmov += abs(curr - prev);
    prev = curr;
    curr = DISKSTART;
    hdmov += abs(curr - prev);
    prev = curr;
    printf("%2d ", curr);

    while (i < h) {
        printf("%2u ", curr = diskqueue[i++]);
        hdmov += abs(curr - prev);
        prev = curr;
    } puts("");

    printf("Total head movement is %d.\n", hdmov);
}

int main(void)
{
    size_t n;
    printf("No. of requests: ");
    scanf("%zu", &n);

    int diskqueue[n];
    printf("\nREQUEST QUEUE (%d-%d)\n>>> ", DISKSTART, DISKEND);
    for (size_t i = 0; i < n; ++i)
        scanf("%d", &diskqueue[i]);
    puts("");

    int head;
    printf("Head at: ");
    scanf("%d", &head);
    puts("");

    if (search(diskqueue, n, head) == n) {
        printf("Head %d is not in queue.\n", head);
        return 1;
    }

    fcfs_schedule(diskqueue, n, head);
    scan_schedule(diskqueue, n, head);
    cscan_schedule(diskqueue, n, head);

    return 0;
}
