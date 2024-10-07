#include <stdio.h>
#include <stdbool.h>

/* Queue Definitions */
#define QUEUE_SIZE 5
char queue[QUEUE_SIZE];
enum {
    FULL,
    NEUTRAL,
    EMPTY
} qs = EMPTY; /* qs stands for “queue state.” */
long r = 0, f = 0;

void enq_r(char x)
{
    queue[r] = x; r = (r + 1) % QUEUE_SIZE;
    if (r == f) qs = FULL;
    else qs = NEUTRAL;
}

char deq_r()
{
    if (r == 0) r = QUEUE_SIZE - 1 ; else r = (r - 1) % QUEUE_SIZE;
    if (r == f) qs = EMPTY;
    else qs = NEUTRAL;
    return queue[r];
}

void enq_f(char x)
{
    if (f == 0) f = QUEUE_SIZE - 1; else f = (f - 1) % QUEUE_SIZE;
    queue[f] = x;
    if (r == f) qs = FULL;
    else qs = NEUTRAL;
}

char deq_f()
{
    char x = queue[f]; f = (f + 1) % QUEUE_SIZE;
    if (r == f) qs = EMPTY;
    else qs = NEUTRAL;
    return x;
}

void display()
{
    printf("Queue: ");
    if (qs == EMPTY) printf("-/-");
    else  {
        size_t i = f;
        do {
            printf("%c", queue[i]);
            i = (i + 1) % QUEUE_SIZE;
        } while (i != r);
    } puts("");
}
/* END: Qeueue Definitions */

int main()
{
    char choice;
    while (true) {
        printf("Front: %zu\tRear: %zu\n", f, r);
        printf("(1) Front Enqueue  (2) Front Dequeue\n"
               "(3) Rear Enqueue   (4) Rear Dequeue\n"
               "(5) Display        (q) Quit\nChoice: ");
        scanf(" %c", &choice);
        puts("");
        switch(choice) {
            case '1': {
                if (qs == FULL) puts("The queue is full.");
                else {
                    char x;
                    printf("Element: "); scanf(" %c", &x);
                    enq_f(x);
                } break;
            }
            case '2':
                if (qs == EMPTY) puts("The queue is empty.");
                else printf("Element: %c\n", deq_f());
                break;
            case '3': {
                if (qs == FULL) puts("The queue is full.");
                else {
                    char x;
                    printf("Element: "); scanf(" %c", &x);
                    enq_r(x);
                } break;
            }
            case '4':
                if (qs == EMPTY) puts("The queue is empty.");
                else printf("Element: %c\n", deq_r());
                break;
            case '5':
                display();
                break;
            case 'q':
                return 0;
            default:
                printf("%c is not a valid choice.\n", choice);
                break;
        }
        puts("");
    }
    return 0;
}
