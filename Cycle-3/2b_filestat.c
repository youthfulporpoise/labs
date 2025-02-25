/* QUESTION 2(b).
 * Write a program that uses stat() to retrieve and display file metadata (viz.
 * size; permission; last modified) of a file.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return 0;
    }

    struct stat flattr;
    int rv = stat(argv[1], &flattr);
    if (rv < 0) {
        perror(argv[1]);
        return 1;
    }

    char *atime = ctime(&flattr.st_atim.tv_sec),
         *mtime = ctime(&flattr.st_mtim.tv_sec);

    printf(
        "File: %s\n"
        "Size: %zuB\n"
        "Permissions: %o\n"
        "Last access: %s"
        "Last modification: %s",
        argv[1],
        flattr.st_size,
        flattr.st_mode,
        atime,
        mtime
    );

    return 0;
}
