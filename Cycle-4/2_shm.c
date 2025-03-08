/* QUESTION 2.
 * Write a C program to implement inter-process communication using shared
 * memory. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <string.h>
#include <signal.h>

/* We need a semaphore mutex to coordinate read and write between processes in
 * the shared memory. */
sem_t *mutex, *avail;

/* This is our shared memory buffer. */
#define BUFFER_SIZE 1024
char *buffer;
int prot = PROT_READ | PROT_WRITE;
int flag = MAP_ANONYMOUS | MAP_SHARED;


void sighandler(int sig)
{
    sem_close(mutex);
    sem_close(avail);
    munmap(buffer, BUFFER_SIZE);
    puts("\nExiting ...");
    exit(4);
}


int main(void)
{
    signal(SIGINT, sighandler);

    buffer = mmap(NULL, BUFFER_SIZE, prot, flag, -1, 0);
    mutex = sem_open("/mutex", O_CREAT, 0644, 1);
    avail = sem_open("/avail", O_CREAT, 0644, 0);

    pid_t pid = fork();
    if (pid == 0) {
        mutex = sem_open("/mutex", 0);
        avail = sem_open("/avail", 0);

        if (sem_wait(mutex) < 0)
            perror("mutex");

        puts("WRITE:");
        scanf("%[^\n]", buffer);
        printf("\nWritten %zu bytes to shared memory.\n", strlen(buffer));

        if (sem_post(avail) < 0)
            perror("avail: post");
        sem_post(mutex);
        return 0;
    } else {
        mutex = sem_open("/mutex", 0);
        avail = sem_open("/avail", 0);

        if (sem_wait(avail) < 0)
            perror("avail: wait");
        if (sem_wait(mutex) < 0)
            perror("mutex");

        puts("\nREAD");
        printf("%s\n", buffer);
        sem_post(mutex);

        sem_close(avail);
        sem_close(mutex);

        munmap(buffer, BUFFER_SIZE);
        return 0;
    }
}
