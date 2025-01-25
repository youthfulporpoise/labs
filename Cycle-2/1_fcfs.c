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
enum { FULL, EMPTY, NEUTRAL } = EMPTY;

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
    unsigned end;
} Gantt;

/* A Gantt chart of a certain size is provided to do with. */
Gantt chart[64];

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

void fcfs(Process *process, size_t n)
{
    sort(process, n);
}
