/* QUESTION 1.
 * Write a C program to simluate producer-consumer using semaphores and threads.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>
#include <signal.h>

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
sem_t *empty, *full, *mutex;

/* The mutex lock associated with the buffer queue. */
// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


/* The produce function produces and writes a random integer to the shared
 * buffer.  The producer function is a higher-level function that systematically
 * calls the produce function. */
void produce(void)
{
    if (sem_wait(empty) < 0)
        perror("produce: sem_wait");
    if (sem_wait(mutex) < 0)
        perror("mutex: sem_wait");

    long x = random();
    enqueue(x);
    printf("%ld produced.\n", x);

    sem_post(mutex);
    if (sem_post(full) < 0)
        perror("produce: sem_post");

    return;
}

void *producer(void *arg)
{
    for (size_t i = 0; i < 10; ++i) {
        produce();
        usleep(400000);  /* 0.4 sec */
    }
    return NULL;
}


/* The consume function consumes an integer from the shared buffer.  The
 * consumer function is a higher-level function that systematically calls the
 * consume function. */
void consume(void)
{
    if (sem_wait(full) < 0)
        perror("consume: sem_wait");
    if (sem_wait(mutex) < 0)
        perror("mutex: sem_wait");

    printf("%ld consumed.\n", dequeue());

    sem_post(mutex);
    if (sem_post(empty) < 0)
        perror("consume: sem_wait");

    return;
}

void *consumer(void *arg)
{
    for (size_t i = 0; i < 10; ++i) {
        consume();
        usleep(700000);  /* 0.7 sec */
    }
    return NULL;
}

/* The producer and consumer functions call their corresponding primitives as
 * much times as the size of the shared buffer.  Therefore, the number produce
 * and consume calls are adjusted by adjusting the size of the shared buffer.
 * These two functions call their primitives with an interval.  The interval is
 * prime-number long.  The produce and consume functions both have different
 * intervals from each other that are prime. */

void sighandle(int sig)
{
    sem_close(full);
    sem_close(empty);
    sem_close(mutex);
    puts("\nExiting ...");
    exit(8);
}

int main(int argc, char **argv)
{
    signal(SIGINT, sighandle);

    /* There is read-write for all. */
    mode_t perm = S_IWUSR | S_IRUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

    /* The semaphore name must have a prefix virgule. */
    empty = sem_open("/empty", O_CREAT, perm, BUFFER_SIZE);
    full = sem_open("/full", O_CREAT, perm, 0);
    mutex = sem_open("/mutex", O_CREAT, perm, 1);

    pthread_t tp, tc;
    pthread_create(&tp, NULL, &producer, NULL);
    pthread_create(&tc, NULL, &consumer, NULL);

    if (pthread_join(tp, NULL) != 0)
        perror("pthread tp");
    if (pthread_join(tc, NULL) != 0)
        perror("pthread tc");
    
    sem_close(empty);
    sem_close(full);
    sem_close(mutex);
    return 0;
}
