#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

/* A process defined by its ID, arrival time, and burst time. */
typedef struct {
    size_t id;   /* Process ID */
    unsigned at; /* Arrival time */
    unsigned bt; /* Burst time */
} Process;
/* The valid process IDs of a nontrivial process can be any of 1, 2, ...
 * The process ID zero is the trivial process (a null process or nothing
 * process).  This ID must be reserved. */

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


/* A Gantt chart of a certain size is provided to do with. */
typedef size_t Gantt;
Gantt chart[32];

/* This is our sorting function. */
/* Complexity: O(n)  O(n^2)  O(n^2) */
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

/* This function produces a Gantt chart from a process table.
 * Note: The process table is consumed.  Ensure a copy if later needed. */
/* Complexity: O(z) where z is total burst time. */
size_t fcfs(Process *process, size_t n)
{
    sort(process, n);

    size_t z = 0;    /* The current chart element. */
    size_t i = 0;    /* The current process from table. */
    unsigned t = 0;  /* The current time. */
    bool busy = false;
    Process p;

    while (true) {
        while (i < n && t == process[i].at)
            enqueue(process[i++]);

        if (!busy) {
            if (qs == EMPTY) {
                if (i < n) chart[t++] = 0;
                else break;
            } else {
                p = dequeue();
                busy = true;
            }
        } else {
            chart[t++] = p.id;
            p.bt--;
            if (p.bt == 0) busy = false;
        }
    }

    return t;
}

/* This function prints our Gantt chart. */
/* Complexity: O(z) where z is the total burst time. */
void print_chart(char *msg, Gantt *chart, size_t n)
{
    printf("%s", msg);
    for (size_t i = 0; i < n; ++i)
        printf("%zu ", chart[i]);
    puts("");

    /* The process being executed, initialized to the trivial process. */
    Gantt ex = 0;
    size_t t;
    for (t = 0; t < n; ++t) {
        if (ex == chart[t]) continue;
        else {
            if (chart[t] == 0)
                printf("%zu  ", t);
            else
                printf("%zu  [ P%zu ]  ", t, chart[t]);
            ex = chart[t];
        }
    } printf("%zu\n", t);
}

/* This function prints a result table from a Gantt chart. */
/* Complexity: O(n z) */
void print_table
    (char *msg, Process *process, size_t n, Gantt *chart, size_t z)
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
        printf("P%-7zu %8zu %8zu\n", p.id, wt, tt);
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
