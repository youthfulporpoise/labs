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
sem_t *sem;

/* The mutex lock associated with the action chronology counter. */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


/* The write-out to standard out is not guaranteed to be chronological.  The
 * action count assists in keeping track the chronology.  Each action increment
 * is mutually exclusive. */
size_t actionc = 0;
size_t action()
{
    pthread_mutex_lock(&mutex);
    actionc++;
    pthread_mutex_unlock(&mutex);
    return actionc;
}


/* The produce function produces and writes a random integer to the shared
 * buffer.  The producer function is a higher-level function that systematically
 * calls the produce function. */
void produce()
{
    sem = sem_open("buffer", 0);
    long x = random();
    enqueue(x);
    printf("%ld produced. [%zu]\n", x, action());
    if (sem_post(sem) < 0)
        perror("sem_post");

    return;
}

void *producer(void *arg)
{
    for (size_t i = 0; i < BUFFER_SIZE; ++i) {
        produce();
        usleep(13);
    }
    return NULL;
}


/* The consume function consumes an integer from the shared buffer.  The
 * consumer function is a higher-level function that systematically calls the
 * consume function. */
void consume()
{
    sem = sem_open("buffer", 0);
    if (sem_wait(sem) < 0)
        perror("sem_wait");
    printf("%ld consumed. [%zu]\n", dequeue(), action());

    return;
}

void *consumer(void *arg)
{
    for (size_t i = 0; i < BUFFER_SIZE; ++i) {
        consume();
        usleep(43);
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
    sem_t *sem = sem_open("buffer", O_CREAT, 0644, 0);

    pthread_create(&tc, NULL, &consumer, NULL);
    pthread_create(&tp, NULL, &producer, NULL);

    pthread_join(tp, NULL);
    pthread_join(tc, NULL);
    
    sem_close(sem);
    return 0;
}
