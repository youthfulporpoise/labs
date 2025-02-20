#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();
    if (pid < 0) {
        printf("fork failure\n");
        exit(1);
    } else if (pid == 0) {
        printf("PID: %d\n", getpid());
        execl("/bin/ls", "ls", NULL);
        return 0;
    } else {
        wait(NULL);
        return 0;
    }
}
