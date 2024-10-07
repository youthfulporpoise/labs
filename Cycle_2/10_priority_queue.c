#include <stdio.h>
#include <stdbool.h>

#define QUEUE_SIZE 5
typedef struct {
    char v;
    unsigned p;
} PQ;
PQ queue[QUEUE_SIZE];
size_t r = 0;

PQ __tmp__;
#define SWAP(a, b) { __tmp__ = (a); (a) = (b); (b) = __tmp__; }

void heapify_up(PQ* queue, size_t i)
{
    if (i < 1) return;
    size_t p = (i - 1) / 2;
    if (queue[i].p > queue[p].p) {
        SWAP(queue[i], queue[p]);
        heapify_up(queue, p);
    } else return;
}

void heapify_down(PQ* queue, size_t i, size_t n)
{
    size_t lc = 2 * i + 1,
           rc = 2 * i + 2,
           max = i;
    if (lc < n && queue[lc].p > queue[max].p) max = lc;
    if (rc < n && queue[rc].p > queue[max].p) max = rc;
    if (max == i) return;
    else {
        SWAP(queue[i], queue[max]);
        heapify_down(queue, max, n);
    } return;
}

void enqueue(char v, unsigned p)
{
    queue[r].v = v; queue[r].p = p; r++;
    heapify_up(queue, r - 1);
}

PQ dequeue()
{
    r--; SWAP(queue[0], queue[r]);
    PQ x = queue[r];
    heapify_down(queue, 0, r);
    return x;
}

void display()
{
    printf("Value  Priority\n"
           "-----  --------\n");
    for (size_t i = 0; i < r; ++i)
        printf("%5c  %8u\n", queue[i].v, queue[i].p);
    printf("---------------\n");
}

int main()
{
    char choice;
    while (true) {
        printf("(1) Enqueue  (2) Dequeue  (3) Display  (q) Quit\nChoice: ");
        scanf(" %c", &choice);
        switch(choice) {
            case '1':
                if (r == QUEUE_SIZE) printf("The queue is full.");
                else {
                    char v; unsigned p;
                    printf("Value, Priority: "); scanf(" %c %u", &v, &p);
                    enqueue(v, p);
                } break;
            case '2':
                if (r == 0) puts("The queue is empty.");
                else {
                    PQ x = dequeue();
                    printf("Element: (%c, %u)\n", x.v, x.p);
                } break;
            case '3':
                display();
                break;
            case 'q':
                return 0;
            default:
                printf("%c: invalid choice\n", choice);
                break;
        } puts("");
    }
}
