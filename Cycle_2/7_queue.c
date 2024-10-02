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
size_t r = 0, f = 0;

void enqueue(char x)
{
    queue[r] = x; r = (r + 1) % QUEUE_SIZE;
    if (r == f) qs = FULL;
    else qs = NEUTRAL;
}

char dequeue()
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
        printf("(1) Enqueue  (2) Dequeue  (3) Display  (q) Quit\n"
               "Choice: ");
        scanf(" %c", &choice);
        puts("");
        switch(choice) {
            case '1': {
                if (qs == FULL) puts("The queue is full.");
                else {
                    char x;
                    printf("Element: "); scanf(" %c", &x);
                    enqueue(x);
                } break;
            }
            case '2':
                if (qs == EMPTY) puts("The queue is empty.");
                else printf("Element: %c\n", dequeue());
                break;
            case '3':
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
