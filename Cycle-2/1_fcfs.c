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
size_t r = 0, f = 0;
enum { FULL, EMPTY, NEUTRAL } qs = EMPTY;

void enqueue(Process x)
{
    queue[f] = x;
    f = (f + 1) % QS;
    if (r == f) qs = FULL; else qs = NEUTRAL;
}

Process dequeue()
{
    Process x = queue[r];
    r = (r + 1) % QS;
    if (r == f) qs = EMPTY; else qs = NEUTRAL;
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

    for (size_t i = 0; i < n; ++i)
        enqueue(process[i]);

    size_t z = 0;
    unsigned t = 0;
    while (qs != EMPTY) {
        Gantt c;
        Process p = dequeue();

        if (p.at > t) t = p.at;

        c.id = p.id;
        c.start = t;

        t += p.bt;

        c.stop = t;
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
