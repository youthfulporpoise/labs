#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    ssize_t id;     /* Process ID */   
    size_t at;      /* Arrival time */
    size_t bt;      /* Burst time */
    size_t p;       /* Priority */
} Process;

#define QS 32
Process queue[QS];
size_t r = 0, f = 0;
enum { FULL, EMPTY, NEUTRAL } qs = EMPTY;

Process __tmp__;
#define SWAP(x, y) { __tmp__ = (x); (x) = (y); (y) = __tmp__; }

void enqueue(Process x)
{
    queue[r] = x;

    size_t i = r, p;
    while (i > 0) {
        p = (i - 1) >> 1;
        if (queue[i].p < queue[p].p)
            SWAP(queue[i], queue[p]);
        i = p;
    }
    r++;
    if (r == QS) qs = FULL;
    else qs = NEUTRAL;
}

Process dequeue()
{
    r--;
    SWAP(queue[0], queue[r]);
    Process x = queue[r];

    size_t i = 0;
    size_t lc, rc, min;
    while (i < r) {
        min = i;
        lc = 2 * i + 1;
        rc = 2 * i + 2;
        if (lc < r && queue[lc].p <= queue[min].p)
            min = lc;
        if (rc < r && queue[rc].p <= queue[min].p)
            min = rc;
        if (min == i)
            break;
        else
            SWAP(queue[i], queue[min]);
        i = min;
    }
    if (r == 0) qs = EMPTY;
    else qs = NEUTRAL;

    return x;
}

Process peek()
{
    return queue[0];
}

/* A global chart variable */
ssize_t chart[128];

int compar(const void *a, const void *b)
{
    Process *x = (Process*) a,
            *y = (Process*) b;

    if (x->at < y->at) return -1;
    else if (x->at > y->at) return 1;
    else return 0;
}

size_t prty_sched(Process *process, size_t n)
{
    qsort(process, n, sizeof (Process), compar);

    size_t z = 0;      /* The current chart element. */
    size_t i = 0;      /* The current process from table. */
    unsigned t = 0;    /* The current time. */
    bool busy = false;
    Process p;

    while (true) {
        while (i < n && t == process[i].at)
            enqueue(process[i++]);

        if (!busy) {
            if (qs == EMPTY) {
                if (i < n) chart[t++] = -1;
                else break;
            } else {
                p = dequeue();
                busy = true;
            }
        } else {
            if (qs != EMPTY && p.p > peek().p) {
                enqueue(p);
                p = dequeue();
            }
            chart[t++] = p.id;
            p.bt--;
            if (p.bt == 0) busy = false;
        }
    }

    return t;
}

void print_chart(char *msg, size_t *chart, size_t n)
{
    printf("%s", msg);
    for (size_t i = 0; i < n; ++i)
        printf("%ld ", chart[i]);
    puts("");

    ssize_t ex = -1;
    size_t t;
    for (t = 0; t < n; ++t) {
        if (ex == chart[t]) continue;
        else {
            if (chart[t] < 0)
                printf("%zu  ", t);
            else
                printf("%zu  [ P%ld ]  ", t, chart[t]);
            ex = chart[t];
        }
    } printf("%zu\n", t);
}

void print_table
    (char *msg, Process *process, size_t n, ssize_t *chart, size_t z)
{
    printf("%s", msg);

    size_t wtc = 0, ttc = 0;
    size_t wt = 0, tt = 0;
    Process p;

    printf("ID       WT (ms)  TT (ms)  \n"
           "········ ········ ········ \n");
    for (size_t i = 0; i < n; ++i, wt = 0, tt = 0) {
        p = process[i];
        for (size_t t = 0; t < z; ++t)
            if (chart[t] == p.id)
                tt = t + 1;
        for (size_t t = 0; t < tt; ++t)
            if (chart[t] != p.id)
                wt++;
        wt -= p.at;
        tt -= p.at;
        printf("P%-7ld %8zu %8zu\n", p.id, wt, tt);
        wtc += wt;
        ttc += tt;
    }
    printf("········ ········ ········  \n");
    printf("Avg.     %8zu %8zu\n", wtc / n, ttc / n);
}

int main()
{
    size_t n;
    printf("Number of processes: ");
    scanf("%zu", &n);

    printf("ID    Arrival Time    Burst Time    Priority:\n");
    Process process[n];
    for (size_t i = 0; i < n; ++i) {
        Process p;
        scanf("%ld %zu %zu %zu", &p.id, &p.at, &p.bt, &p.p);
        process[i] = p;
    }

    size_t z = prty_sched(process, n);

    print_chart("\nGANTT CHART\n", chart, z);
    print_table("\nRESULT\n", process, n, chart, z);

    return 0;
}
