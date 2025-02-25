/* QUESTION 2(a)
 * Write a C program that opens a file, writes data to it, and closes it.
 * Then, reopen the file, read the data, and display the contents.
 * Use open, write, read, and close.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define CONTL 1024

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usage: %s <path>\n", argv[0]);
        exit(0);
    }

    /* Writing to file. */
    int fd = open(argv[1], O_CREAT | O_WRONLY, 0644);
    /* Create (if inexistent) and open for write. */
    /* Permissions: -rw-r--r--  student   (644) */
    printf("Opened \"%s\" for W.\n", argv[1]);

    char contw[CONTL];
    printf("CONTENT:\n");
    scanf("%[^\n]", contw);

    size_t contc = strlen(contw);
    write(fd, contw, contc);
    printf("\nWritten %zu bytes.\n", contc);
    close(fd);

    /* Reading from file. */
    fd = open(argv[1], O_RDONLY);
    printf("\nOpened \"%s\" for R.\n", argv[1]);
    
    char contr[CONTL];
    read(fd, contr, contc);
    contr[contc] = '\0';

    printf("READ\n%s\n", contr);
    close(fd);

    return 0;
}
