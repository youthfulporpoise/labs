#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct {
    ssize_t id;   
    size_t at;
    size_t bt; 
} Process;

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

ssize_t chart[32];

int compar(const void *a, const void *b)
{
    Process *x = (Process*) a,
            *y = (Process*) b;

    if (x->at < y->at) return -1;
    else if (x->at > y->at) return 1;
    else return 0;
}

size_t schedule(Process *process, size_t n)
{
    qsort(process, n, sizeof (Process), compar);

    size_t z = 0;    /* The current chart element. */
    size_t i = 0;    /* The current process from table. */
    size_t t = 0;  /* The current time. */
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
            chart[t++] = p.id;
            p.bt--;
            if (p.bt == 0) busy = false;
        }
    }

    return t;
}

void print_chart(char *msg, ssize_t *chart, size_t n)
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
            if (chart[t] == -1)
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
        scanf("%zu %zu %zu", &p.id, &p.at, &p.bt);
        process[i] = p;
    }

    size_t z = schedule(process, n);

    print_chart("\nGANTT CHART\n", chart, z);
    print_table("\nRESULT\n", process, n, chart, z);

    return 0;
}
