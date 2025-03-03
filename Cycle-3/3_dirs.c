/* QUESTION 3.
 * Write a C program that opens a directory using opendir() and sets all the
 * contents (files and directories inside) using readdir().  For each print the
 * name and whether it is a file or directory.
 */

#include<stdio.h>
#include<dirent.h>

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        return 0;
    }

    char *dirname = argv[1];
    DIR *dir = opendir(dirname);
    if (dir == NULL) {
        perror(dirname);
        return 1;
    }

    char *ftype;
    struct dirent *dentry;
    dentry = readdir(dir);
    if (dentry == NULL) {
        perror(dirname);
        return 1;
    }

    while (dentry != NULL) {
        switch (dentry->d_type) {
            case DT_DIR:
                ftype = "directory";
                break;
            case DT_REG:
                ftype = "regular file";
                break;
            default:
                ftype = "neither a directory nor a regular file";
                break;
        }
        printf("%-20s %-20s\n", dentry->d_name, ftype);
        dentry = readdir(dir);
    }

    return 0;
}
