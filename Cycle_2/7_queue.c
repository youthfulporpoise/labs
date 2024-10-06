#include <stdio.h>
#include <stdbool.h>

#define QUEUE_SIZE 2
char queue[QUEUE_SIZE];
size_t r = 0, f = 0;
void enqueue(char x) { queue[r++] = x; }
char dequeue() { return queue[f++]; }
void display()
{
    printf("Queue: ");
    for (size_t i = f; i < r; i++) printf("%c", queue[i]);
    puts("");
}

int main()
{
    char choice;
    while (true) {
        printf("(1) Enqueue  (2) Dequeue  (3) Display  (q) Quit\n"
               "Choice: ");
        scanf(" %c", &choice);
        puts("");
        switch (choice) {
            case '1': {
                if (r >= QUEUE_SIZE) puts("The queue is full.");
                else {
                    char x; printf("Element: "); scanf(" %c", &x);
                    enqueue(x);
                } break;
            }
            case '2':
                if (r == 0) puts("The queue is empty.");
                else if (f == QUEUE_SIZE) puts("The queue is exhausted.");
                else printf("Element: %c\n", dequeue());
                break;
            case '3':
                display();
                break;
            case 'q':
                return 0;
            default:
                printf("%c: not a valid choice\n", choice);
                break;
        } puts("");
    }
}
