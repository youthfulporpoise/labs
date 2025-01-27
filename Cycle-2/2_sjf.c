#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

/* A process defined by its ID, arrival time, and burst time. */
typedef struct {
    size_t id;   /* Process ID */
    unsigned at; /* Arrival time */
    unsigned bt; /* Burst time */
} Process;

/* A queue of a certain size is provided to do with. */
#define QS 32
Process queue[QS];
size_t r = 0;
enum { FULL, EMPTY, NEUTRAL } qs = EMPTY;

Process __tmp__;
#define SWAP(x, y) { __tmp__ = (x); (x) = (y); (y) = __tmp__; }

/* Complexity: log2(n) */
void enqueue(Process x)
{
    queue[r] = x;

    size_t i = r;
    size_t lc, rc, p, min;
    while (i > 0) {
        min = p = i / 2;
        lc = 2 * p + 1;
        rc = 2 * p + 2;
        if (queue[min].bt > queue[lc].bt) min = lc;
        if (queue[min].bt > queue[rc].bt) min = rc;
        if (min == p)
            break;
        else
            SWAP(queue[p], queue[min]);
        i = p;
    }
    r++;
    if (r == QS) qs = FULL;
    else qs = NEUTRAL;
}

/* Complexity: log2(n) */
Process dequeue()
{
    SWAP(queue[0], queue[r]);
    Process x = queue[r--];

    size_t i = 0;
    size_t lc, rc, min;
    while (i < r) {
        min = i;
        lc = 2 * i + 1;
        rc = 2 * i + 2;
        if (queue[lc].bt <= queue[min].bt) min = lc;
        if (queue[rc].bt <= queue[min].bt) min = rc;
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

/* A Gantt element has an ID, starting time, and ending time. */
typedef struct {
    size_t id;
    unsigned start;
    unsigned stop;
} Gantt;

/* A Gantt chart of a certain size is provided to do with. */
Gantt chart[32];

/* This is our sorting function. */
void sort(Process *process, size_t n)
{
    /* We are using insertion sort. */
    for (size_t i = 1; i < n; ++i) {
        size_t j = i;
        Process x = process[i];
        while (j > 0 && x.at < process[j - 1].at) {
            process[j] = process[j - 1];
            --j;
        } process[j] = x;
    }
}

/* This function produces a Gantt chart from a process table. */
size_t fcfs(Process *process, size_t n)
{
    sort(process, n);

    Process x;      /* The current process. */
    size_t z = 0;   /* The current Gantt element. */
    size_t i = 0;   /* The current process from table. */
    unsigned t = 0; /* The current time. */
    while (true) {
        if (i < n && process[i].at == t)
            enqueue(process[i++]);

        if (qs == EMPTY) break;
        else x = dequeue();

        while (t < x.at) {
            t++;
            if (i < n && process[i].at == t)
                enqueue(process[i++]);
        }

        Gantt c;
        c.id = x.id;
        c.start = t;
        c.stop = (t += x.bt);
        chart[z++] = c;
    }
    return z;
}

/* This function prints our Gantt chart. */
void print_chart(char *msg, Gantt *chart, size_t n)
{
    printf("%s", msg);
    size_t z;
    for (z = 0; z < n; ++z) 
        printf("%u  [ P%zu ]  %u  ", chart[z].start, chart[z].id, chart[z].stop);
    puts("");
}

/* This function prints a result table from a Gantt chart. */
void print_table
    (char *msg, Process *process, size_t n, Gantt *chart, size_t z)
{
    printf("%s", msg);
    printf("ID       WT (ms)  TT (ms)  \n"
           "········ ········ ········ \n");
    /* The accumulators for waiting times and turn-around times. */
    /* These are waiting time and turn-around time. */
    /* k-th is the turn-around Gantt element. */
    unsigned wtc = 0, ttc = 0;
    unsigned wt, tt;
    size_t k;

    for (size_t i = 0; i < n; ++i) {
        Process p = process[i];
        k = 0;
        tt = 0;
        for (size_t j = 0; j < z; ++j)
            if (p.id == chart[j].id)
                tt = chart[k = j].stop;
        wt = 0;
        for (size_t j = 0; j <= k; ++j)
            if (p.id != chart[j].id)
                wt += chart[j].stop - chart[j].start;
        tt -= p.at;
        printf("P%-7zu %8u %8u\n", p.id, wt, tt);

        wtc += wt;
        ttc += tt;
    }
    printf("········ ········ ········  \n");
    printf("Avg.     %-8u %-8u \n",
           wtc / (unsigned) n,
           ttc / (unsigned) n);
}

int main()
{
    size_t n;
    printf("Number of processes: ");
    scanf("%zu", &n);

    printf("ID    Arrival Time    Burst Time:\n");
    Process process[n];
    for (size_t i = 0; i < n; ++i) {
        Process p;
        scanf("%zu %u %u", &p.id, &p.at, &p.bt);
        process[i] = p;
    }

    size_t z = fcfs(process, n);
    print_chart("\nGANTT CHART\n", chart, z);
    print_table("\nRESULT\n", process, n, chart, z);

    return 0;
}
