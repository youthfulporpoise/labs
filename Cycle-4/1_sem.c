/* QUESTION 1.
 * Write a C program to simluate producer-consumer using semaphores and threads.
 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<semaphore.h>
#include<pthread.h>

/* This is our shared buffer between producer and consumer threads.  The shared
 * buffer is a circular queue, accessible through enqueue and dequeue
 * operations. */
#define BUFFER_SIZE 4
long buffer[BUFFER_SIZE];
size_t r = 0, f = 0;

void enqueue(long x)
{
    buffer[r] = x;
    r = (r + 1) % BUFFER_SIZE;
}

long dequeue()
{
    long x = buffer[f];
    f = (f + 1) % BUFFER_SIZE;
    return x;
}


/* The semaphore reference associated with our shared buffer. */
sem_t *empty, *full;

/* The mutex lock associated with the buffer queue. */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


/* The produce function produces and writes a random integer to the shared
 * buffer.  The producer function is a higher-level function that systematically
 * calls the produce function. */
void produce()
{
    empty = sem_open("empty", 0);
    full = sem_open("full", 0);

    if (sem_wait(empty) < 0) perror("produce: sem_wait");

    pthread_mutex_lock(&mutex);
    long x = random();
    enqueue(x);
    printf("%ld produced.\n", x);
    pthread_mutex_unlock(&mutex);

    if (sem_post(full) < 0) perror("produce: sem_post");

    return;
}

void *producer(void *arg)
{
    for (;;) {
        produce();
        usleep(433000);
    }
    return NULL;
}


/* The consume function consumes an integer from the shared buffer.  The
 * consumer function is a higher-level function that systematically calls the
 * consume function. */
void consume()
{
    empty = sem_open("empty", 0);
    full = sem_open("full", 0);

    if (sem_wait(full) < 0) perror("consume: produce");

    pthread_mutex_lock(&mutex);
    printf("%ld consumed.\n", dequeue());
    pthread_mutex_unlock(&mutex);

    if (sem_post(empty) < 0) perror("consume: sem_wait");

    return;
}

void *consumer(void *arg)
{
    for (;;) {
        consume();
        usleep(733000);
    }
    return NULL;
}

/* The producer and consumer functions call their corresponding primitives as
 * much times as the size of the shared buffer.  Therefore, the number produce
 * and consume calls are adjusted by adjusting the size of the shared buffer.
 * These two functions call their primitives with an interval.  The interval is
 * prime-number long.  The produce and consume functions both have different
 * intervals from each other that are prime. */

int main(int argc, char **argv)
{
    pthread_t tp, tc;
    empty = sem_open("empty", O_CREAT, 0644, BUFFER_SIZE);
    full = sem_open("full", O_CREAT, 0644, 0);

    pthread_create(&tp, NULL, &producer, NULL);
    pthread_create(&tc, NULL, &consumer, NULL);

    pthread_join(tp, NULL);
    pthread_join(tc, NULL);
    
    sem_close(empty);
    sem_close(full);
    return 0;
}
