/* QUESTION 1.
 * Write a C program to simluate producer-consumer using semaphores and threads.
 */

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<pthread.h>

/* This is our shared buffer between producer and consumer threads. */
#define BUFFER_SIZE 4
long buffer[BUFFER_SIZE];

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int empty = BUFFER_SIZE;

/* P is the semaphore wait. */
void P(int *s)
{
    --(*s);
}

/* V is the semaphore signal or post. */
void V(int *s)
{
    ++(*s);
}


/* The produce function produces and writes a random integer to the shared
 * buffer.  The producer function is a higher-level function that systematically
 * calls the produce function. */
void produce()
{
    pthread_mutex_lock(&mutex);

    if (empty == 0) {
        printf("The buffer is full.\n");
        pthread_mutex_unlock(&mutex);
        return;
    }
    P(&empty);
    buffer[empty] = random();
    printf("%ld produced.\n", buffer[empty]);

    pthread_mutex_unlock(&mutex);
    return;
}

void *producer(void *arg)
{
    for (size_t i = 0; i < BUFFER_SIZE; ++i) {
        produce();
        usleep(23);
    }
    return NULL;
}


/* The consume function consumes an integer from the shared buffer.  The
 * consumer function is a higher-level function that systematically calls the
 * consume function. */
void consume()
{
    pthread_mutex_lock(&mutex);

    if (empty == BUFFER_SIZE) {
        printf("The buffer is empty.\n");
        pthread_mutex_unlock(&mutex);
        return;
    }
    printf("%ld consumed.\n", buffer[empty]);
    V(&empty);

    pthread_mutex_unlock(&mutex);
    return;
}

void *consumer(void *arg)
{
    for (size_t i = 0; i < BUFFER_SIZE; ++i) {
        consume();
        usleep(13);
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

    pthread_create(&tp, NULL, &producer, NULL);
    pthread_create(&tc, NULL, &consumer, NULL);

    pthread_join(tp, NULL);
    pthread_join(tc, NULL);
    
    return 0;
}
