/* QUESTION 1.
 * Write a C program to simluate producer-consumer using semaphores and threads.
 */

#include<stdio.h>
#include<stdlib.h>

#define BUFFER_SIZE 4
long buffer[BUFFER_SIZE];

int mutex = 1,
    empty = BUFFER_SIZE;

int signal(int *s) { ++(*s); }
int wait(int *s) { --(*s); }

/* This function produces a random long integer. */
void produce()
{
    if (mutex == 0) return;
    else if (empty == 0) {
        printf("\nThe buffer is full.\n");
        return;
    }
    wait(&mutex);
    buffer[empty] = random();
    printf("%ld produced.\n", buffer[empty]);
    wait(&empty);
    signal(&mutex);
}

/* This function consumes an entry from the buffer. */
void consume()
{
    if (mutex == 0) return;
    else if (empty == BUFFER_SIZE) {
        printf("\nThe buffer is empty.\n");
        return;
    }
    wait(&mutex);
    signal(&empty);
    printf("%ld consumed.\n", buffer[empty]);
    signal(&mutex);
}

int main(int argc, char **argv)
{
    produce();
    produce();
    consume();
    produce();
    consume();
    consume();
    produce();
    consume();

    return 0;
}
